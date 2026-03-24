#pragma once

#include <macros/nyMacros.hpp>

#include "macros/nyCoreApi.hpp"

#include "types/nyStatus.hpp"
#include "types/nyTypes.hpp"

#include "thread/nyMutex.hpp"
#include "thread/nyThread.hpp"

namespace nyEngineSDK
{
  class NY_API BaseApp
  {
   public:
    /**
     * @brief  Default constructor
     * @bug    No known bugs
     */
    BaseApp() = default;
    /**
     * @brief  Default destructor
     * @bug    No known bugs
     */
    virtual
    ~BaseApp() = default;

    /**
     * @brief  Tells every module and system to initialize and starts the main loop.
     * @return The finish code, tells if there was any error.
     * @bug    No known bugs
     */
    virtual Status
    run();

   protected:
    /**
     * @brief  The init event function for the app derivate to override.
     *         It's called after the base app initializes all modules and systems.
     * @bug    No known bugs
     */
    virtual void
    onInit(){}

    /**
     * @brief  The update event function for the app derivate to override.
     *         It's called every frame after updating every system.
     * @param  deltaTime  Time elapsed since last frame.
     * @bug    No known bugs
     */
    virtual void
    onUpdate(NY_MAYBE_UNUSED float deltaTime){};

    /**
     * @brief  The render event function for the app derivate to override.
     *         It's called every frame after rendering every entity and UI.
     * @bug    No known bugs
     */
    virtual void
    onRender(){};

    /**
     * @brief  The destroy event function for the app derivate to override.
     *         It's called before releasing and destroying everything in the app.
     * @bug    No known bugs
     */
    virtual void
    onDestroy(){};

   private:
    /**
     * @brief  Keeps the application running, make the input/update loop.
     * @return The finish code, tells if there was any error.
     * @bug    No known bugs
     */
    Status
    gameLoop();

    /**
     * @brief  Keeps the application rendering, make the render loop.
     * @return The finish code, tells if there was any error.
     * @bug    No known bugs
     */
    Status
    renderLoop();
  
    /**
     * @brief  Returns true if the APP should still be running every frame.
     * @return Weather it can still run or not.
     * @bug    No known bugs
     */
    bool
    appIsRunning();
  
    /**
     * @brief  Initializes systems and modules for everything in the app.
     * @return A Status object that tells if everything succeeded or if there
     *         was an error and what happened.
     * @bug    No known bugs
     */
    Status
    init();
  
    /**
     * @brief  Initializes the systems that the app needs, like the graphics,
     *         mesh loading, inputs, etc.
     * @return A Status object that tells if everything succeeded or if there
     *         was an error and what happened.
     * @bug    No known bugs
     */
    Status
    initSystems();
  
    /**
     * @brief  Called every game frame of the game loop to let everything update.
     * @bug    No known bugs
     */
    void
    update();
  
    /**
     * @brief  Called at the end of every game frame of the game loop to let
     *         everything know the update is about to end.
     * @bug    No known bugs
     */
    void
    lateUpdate();
  
    /**
     * @brief  Called every fixed time in the game loop to let everything update.
     * @bug    No known bugs
     */
    void
    fixedUpdate();
  
    /**
     * @brief  Called at the end of every fixed update to let everything know
     *         the update is about to end.
     * @bug    No known bugs
     */
    void
    lateFixedUpdate();
  
    /**
     * @brief  Called every frame of the render loop. Tells the render module,
     *         if there is any, to render.
     * @bug    No known bugs
     */
    void
    render();
  
    /**
     * @brief  Cleans all the memory allocated during the application run.
     * @bug    No known bugs
     */
    void
    destroy();
  
   protected:
    /**
     * @brief  The game loop thread
     */
    Thread mGameThread;
    /**
     * @brief  The game loop mutex, to synchronize memory access.
     */
    Mutex mGameMutex;

    /**
     * @brief  The render loop thread
     */
    Thread mRenderThread;
    /**
     * @brief  The render loop mutex, to synchronize memory access.
     */
    Mutex mRenderMutex;

    /**
     * @brief  The width of the screen.
     */
    const u32 screenWidth = 1280u;
    /**
     * @brief  The height of the screen.
     */
    const u32 screenHeight = 720u;
  };
}