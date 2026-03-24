#include "BaseApp.h"

#include <thread/nyTime.hpp>

namespace nyEngineSDK
{
  Status
  BaseApp::run()
  {
    auto status = init();
    if (status.isError()) {
      destroy();
      return status;
    }

    /*mRenderThread.start([&]()
    {
      status = renderLoop();
      if (status.isError()) {
        return;
      }

      status = Status::ok();
    });*/

    status = gameLoop();
    if (status.isError()) {
      destroy();
      return status;
    }

    destroy();

    return Status::ok();
  }

  Status
  BaseApp::gameLoop()
  {
    static Duration fixedTimeSum = Duration();
    static Duration fixedDeltaTime = Duration::fromSecondsF(0.02f);
    static Duration currentTime = Time::now();
    while (appIsRunning()) {
      Duration startFrameTime = Time::now();
      Duration timeElapsed = startFrameTime - currentTime;
      currentTime = startFrameTime;
      fixedTimeSum += timeElapsed;

      update();

      while (fixedTimeSum >= fixedDeltaTime) {
        fixedTimeSum -= fixedDeltaTime;

        fixedUpdate();
        lateFixedUpdate();
      }

      lateUpdate();
      render();
    }

    destroy();

    return Status::ok();
  }

  Status
  BaseApp::renderLoop()
  {
    while (appIsRunning()) {
      render();
    }

    return Status::ok();
  }

  bool
  BaseApp::appIsRunning()
  {
    return false;
  }

  Status
  BaseApp::init()
  {
    return Status::ok();
  }

  Status
  BaseApp::initSystems()
  {
    return Status::ok();
  }

  void
  BaseApp::update()
  {
  }

  void
  BaseApp::lateUpdate()
  {
  }

  void
  BaseApp::fixedUpdate()
  {
  }

  void
  BaseApp::lateFixedUpdate()
  {
  }

  void
  BaseApp::render()
  {
  }

  void
  BaseApp::destroy()
  {
  }
}