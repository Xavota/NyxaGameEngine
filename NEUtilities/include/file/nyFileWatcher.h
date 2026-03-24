/******************************************************************************/
/**
 * @file    nyFile.hpp
 * @author  Dalia Castellanos
 * @date    13/03/2026
 * @brief   A watcher for file changes.
 * 
 * Creates a class that has an internal watch list of files, and runs a callback
 * every time a file is edited and saved. his is useful for hot reload on
 * scripts, shaders or for other engine reloads.
 *
 * @bug	    No known bugs.
 */
 /******************************************************************************/
#pragma once

#include <functional>

#include "macros/nyApi.hpp"

#include "thread/nyMutex.hpp"
#include "thread/nyThread.hpp"
#include "types/nyContainers.h"
#include "types/nyTypes.hpp"
#include "types/nyStringView.hpp"

namespace nyEngineSDK
{
  /**
   * @brief  Type of file system change detected by the watcher.
   * @bug    No known bugs
   */
  enum class FileChangeType : u8
  {
    Added = 0,
    Removed,
    Modified
  };

  /**
   * @brief  Describes one file system change event.
   * @bug    No known bugs
   */
  struct FileChangeEvent
  {
    String path;
    FileChangeType type;
    bool isDirectory = false;
  };

  /**
   * @brief  Polling-based file watcher for hot reload.
   * @bug    No known bugs
   */
  class NY_API FileWatcher
  {
   public:

    using Callback = std::function<void(const FileChangeEvent&)>;
   
    /**
     * @brief  Snapshot metadata for one discovered path.
     * @bug    No known bugs
     */
    struct EntryInfo
    {
      Duration lastWriteTime;
      u64 fileSize = 0;
      bool isDirectory = false;
    };

    /**
     * @brief  Default constructor
     * @bug    No known bugs
     */
    FileWatcher();
    /**
     * @brief  Destroys this watcher, stopping its thread.
     * @bug    No known bugs
     */
    ~FileWatcher();

    /**
     * @brief  Initializes the watcher with a time to check the file each time frame
     * @param  interval  The time interval to check for any changes in the file.
     * @bug    No known bugs
     */
    void
    start(const Duration& interval = Duration(0, 0, 0, 0, 0, 0, 1000));

    /**
     * @brief  Initializes the watcher with a time to check the file each time frame
     * @param  interval  The time interval to check for any changes in the file.
     * @bug    No known bugs
     */
    void
    stop();
    
    /**
     * @brief  Add a path root to the watch list.
     * @param  path       The local path to the directory this watcher is going
     *                    to keep track of.
     * @param  callback   If there are any changes in the directory, this
     *                    callback will trigger with info of what happened.
     * @param  recursive  Whether this should check inside internal directories
     *                    too or just stay at root level.
     * @bug    No known bugs
     */
    void
    watchPath(StringView path, Callback callback, bool recursive = false);

   private:

    /**
     * @brief  Configuration for one watched root.
     * @bug    No known bugs
     */
    struct WatchRoot
    {
      String path;
      Callback callback;
      HashMap<String, EntryInfo> snapshot;
      bool recursive = true;
    };

    /**
     * @brief  The loop this watcher makes to check its watch list files every 
     *         time period. This function is ran in a different thread, owned 
     *         by this object, and it's stopped with the 'stop' function
     * @bug    No known bugs
     */
    void
    run();

    /**
     * @brief  Updates one watched root and collects generated events.
     * @bug    No known bugs
     */
    void
    updateRoot(WatchRoot& root, Vector<FileChangeEvent>& outEvents);

    /**
     * @brief  The watch list of roots to keep watch on.
     */
    Vector<WatchRoot> mRoots;

    /**
     * @brief  The thread owned by this object that runs the check loop.
     */
    Thread mThread;
    /**
     * @brief  Mutex for synchronizing every loop to avoid running conditions.
     */
    Mutex mMutex;

    /**
     * @brief  Whether the thread is running or not.
     */
    bool mRunning = false;
    /**
     * @brief  The interval time to check the files every time frame.
     */
    Duration mInterval;
  };
} // namespace nyEngineSDK