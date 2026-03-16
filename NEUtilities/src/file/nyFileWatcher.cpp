#include "file/nyFileWatcher.h"

#include <filesystem>

#include "macros/nyModuleName.h"

#include "file/nyFile.h"
#include "file/nyPath.h"
#include "thread/nyLockGuard.hpp"
#include "thread/nyTime.hpp"

namespace nyEngineSDK
{
  namespace
  {
    /**
     * @brief  Scans a root path and builds a metadata snapshot.
     * @bug    No known bugs
     */
    HashMap<String, FileWatcher::EntryInfo>
    buildSnapshot(StringView rootPath, bool recursive)
    {
      HashMap<String, FileWatcher::EntryInfo> snapshot;

      String fsRoot = Path::normalize(rootPath);
      std::filesystem::path root(fsRoot);

      if (!std::filesystem::exists(root)) {
        return snapshot;
      }

      FileWatcher::EntryInfo rootInfo;
      rootInfo.isDirectory = std::filesystem::is_directory(root);

      if (!rootInfo.isDirectory) {
        rootInfo.fileSize = static_cast<u64>(std::filesystem::file_size(root));
      }

      {
        const auto writeTime = std::filesystem::last_write_time(root);
        const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
          writeTime.time_since_epoch()
        ).count();
        rootInfo.lastWriteTime = Duration(0, 0, 0, 0, 0, 0, static_cast<u64>(ns));
      }

      snapshot[fsRoot] = rootInfo;

      if (!rootInfo.isDirectory) {
        return snapshot;
      }

      if (recursive) {
        for (const auto& it : std::filesystem::recursive_directory_iterator(root)) {
          FileWatcher::EntryInfo info;
          info.isDirectory = it.is_directory();

          if (!info.isDirectory) {
            info.fileSize = static_cast<u64>(it.file_size());
          }

          {
            const auto writeTime = it.last_write_time();
            const auto ns =
              std::chrono::duration_cast<std::chrono::nanoseconds>(
                writeTime.time_since_epoch()).count();
            info.lastWriteTime = Duration(0, 0, 0, 0, 0, 0, static_cast<u64>(ns));
          }

          snapshot[Path::normalize(it.path().string().data())] = info;
        }
      }
      else {
        for (const auto& it : std::filesystem::directory_iterator(root)) {
          FileWatcher::EntryInfo info;
          info.isDirectory = it.is_directory();

          if (!info.isDirectory) {
            info.fileSize = static_cast<u64>(it.file_size());
          }

          {
            const auto writeTime = it.last_write_time();
            const auto ns =
              std::chrono::duration_cast<std::chrono::nanoseconds>(
                writeTime.time_since_epoch()).count();
            info.lastWriteTime = Duration(0, 0, 0, 0, 0, 0, static_cast<u64>(ns));
          }

          snapshot[Path::normalize(it.path().string().data())] = info;
        }
      }

      return snapshot;
    }

  } // namespace

  FileWatcher::FileWatcher() = default;

  FileWatcher::~FileWatcher()
  {
    stop();
  }

  void
  FileWatcher::start(const Duration& interval)
  {
    LockGuard lock(mMutex);

    if (mRunning) {
      return;
    }

    mInterval = interval;
    mRunning = true;

    mThread.start([this]()
    {
      run();
    });
  }

  void
  FileWatcher::stop()
  {
    {
      LockGuard lock(mMutex);
      if (!mRunning) {
        return;
      }

      mRunning = false;
    }

    if (mThread.isJoinable()) {
      mThread.join();
    }
  }

  void FileWatcher::watchPath(StringView path, Callback callback, bool recursive)
  {
    WatchRoot root;
    root.path = Path::makeAbsolute(path);
    root.callback = std::move(callback);
    root.recursive = recursive;
    root.snapshot = buildSnapshot(root.path.data(), root.recursive);

    LockGuard<Mutex> lock(mMutex);
    mRoots.push_back(std::move(root));
  }

  void
  FileWatcher::run()
  {
    for (;;) {
      Vector<std::pair<Callback, FileChangeEvent>> dispatches;

      {
        LockGuard<Mutex> lock(mMutex);

        if (!mRunning) {
          break;
        }

        for (WatchRoot& root : mRoots) {
          Vector<FileChangeEvent> events;
          updateRoot(root, events);

          for (const FileChangeEvent& event : events) {
            dispatches.push_back({ root.callback, event });
          }
        }
      }

      for (const auto& dispatch : dispatches) {
        if (dispatch.first) {
          dispatch.first(dispatch.second);
        }
      }

      Time::sleep(mInterval);
    }
  }

  void FileWatcher::updateRoot(WatchRoot& root, Vector<FileChangeEvent>& outEvents)
  {
    HashMap<String, EntryInfo> newSnapshot;

    try {
      newSnapshot = buildSnapshot(root.path.data(), root.recursive);
    }
    catch (...) {
      return;
    }

    for (const auto& it : newSnapshot) {
      const String& path = it.first;
      const EntryInfo& newInfo = it.second;

      auto oldIt = root.snapshot.find(path);
      if (oldIt == root.snapshot.end())
      {
        FileChangeEvent event;
        event.path = path;
        event.type = FileChangeType::Added;
        event.isDirectory = newInfo.isDirectory;
        outEvents.push_back(std::move(event));
        continue;
      }

      const EntryInfo& oldInfo = oldIt->second;

      if ((oldInfo.lastWriteTime != newInfo.lastWriteTime) ||
          (!newInfo.isDirectory && (oldInfo.fileSize != newInfo.fileSize)))
      {
        FileChangeEvent event;
        event.path = path;
        event.type = FileChangeType::Modified;
        event.isDirectory = newInfo.isDirectory;
        outEvents.push_back(std::move(event));
      }
    }

    for (const auto& it : root.snapshot)
    {
      const String& path = it.first;
      const EntryInfo& oldInfo = it.second;

      auto newIt = newSnapshot.find(path);
      if (newIt == newSnapshot.end())
      {
        FileChangeEvent event;
        event.path = path;
        event.type = FileChangeType::Removed;
        event.isDirectory = oldInfo.isDirectory;
        outEvents.push_back(std::move(event));
      }
    }

    root.snapshot = std::move(newSnapshot);
  }

} // namespace nyEngineSDK