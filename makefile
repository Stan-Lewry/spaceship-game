OBJS = \
 	src/main.cpp \
	src/Utils/SDLUtils.h \
	src/Utils/SDLUtils.cpp \
	src/Utils/Debug.h \
	src/Utils/Debug.cpp \
	src/Utils/Types.h \
	src/GameEngine.h \
	src/GameEngine.cpp \
	src/SubSystem/SubSystem.h \
	src/SubSystem/SubSystem.cpp \
	src/SubSystem/RendererSubSystem/Renderer2D.h \
	src/SubSystem/RendererSubSystem/Renderer2D.cpp \
	src/SubSystem/RendererSubSystem/IsometricRenderer.h \
	src/SubSystem/RendererSubSystem/IsometricRenderer.cpp \
	src/SubSystem/RendererSubSystem/DebugRenderer.h \
	src/SubSystem/RendererSubSystem/DebugRenderer.cpp \
	src/SubSystem/RendererSubSystem/TextureManager.h \
	src/SubSystem/RendererSubSystem/TextureManager.cpp \
	src/SubSystem/RendererSubSystem/TextureLoader.h \
	src/SubSystem/RendererSubSystem/TextureLoader.cpp \
	src/SubSystem/InputSubSystem/InputSubSystem.h \
	src/SubSystem/InputSubSystem/InputSubSystem.cpp \
	src/SubSystem/PhysicsSubSystem/PhysicsSubSystem.h \
	src/SubSystem/PhysicsSubSystem/PhysicsSubSystem.cpp \
	src/SubSystem/AnimationSubSystem/AnimationSubSystem.h \
	src/SubSystem/AnimationSubSystem/AnimationSubSystem.cpp \
	src/Component/Component.h \
	src/Component/WorldComponent.h \
	src/Component/WorldComponent.cpp \
	src/Component/RenderableComponent.h \
	src/Component/RenderableComponent.cpp \
	src/Component/InputComponent.h \
	src/Component/InputComponent.cpp \
	src/Component/PhysicsComponent.h \
	src/Component/PhysicsComponent.cpp \
	src/Component/AnimationComponent.h \
	src/Component/AnimationComponent.cpp \
	src/Entity/Entity.h \
	src/Entity/SimpleInputEntityTest.h \
	src/Entity/SimpleInputEntityTest.cpp \
	src/Entity/PhysicsEntityTest.h \
	src/Entity/PhysicsEntityTest.cpp \
	src/Entity/SimpleWorldEntity.h \
	src/Entity/SimpleWorldEntity.cpp \
	src/Entity/Camera.h \
	src/Entity/Camera.cpp \
	src/Entity/SpaceshipGame.h \
	src/Entity/SpaceshipGame.cpp \
	
CC = g++

COMPILER_FLAGS = -w -std=c++11

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = Spaceship

all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
		
		
