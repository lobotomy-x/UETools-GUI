#pragma once
#include "DirectWindow11.h"
#include "imgui.h"

#include "definitions.h"
#include "ConfigInstance.h"
#include "Unreal.h"
#include "Math.h"

#include <Windows.h>
#include <algorithm>
#include <thread>






namespace ImGui
{
	struct Viewport
	{
		ImGuiViewport* iViewport;
		ImVec2 iViewportPosition;
		ImVec2 iViewportSize;
	};
	Viewport GetViewport();


	static ImDrawList* drawList;
	ImDrawList* GetDrawList();


	void TextBool(const char* label, const bool& inBool, const char* text_true, const char* text_false, const bool& useColoring, const ImU32& color_true, const ImU32& color_false);
	void TextBool(const char* label, const bool& inBool);
	void TextBoolColored(const char* label, const bool& status);
	void TextBoolPresence(const char* label, const bool& presence);
	void TextBoolPresenceColored(const char* label, const bool& presence);
	void TextBoolMultiplePresence(const char* label, const bool& presence);
	void TextBoolMultiplePresenceColored(const char* label, const bool& presence);


	void TextFloat(const char* label, const float& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative);
	void TextFloat(const char* label, const float& value);
	void TextFloatColored(const char* label, const float& value);


	void TextInt(const char* label, const int32_t& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative);
	void TextInt(const char* label, const int32_t& value);
	void TextIntColored(const char* label, const int32_t& value);


	void TextVector(const char* label, const SDK::FVector& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative);
	void TextVector(const char* label, const SDK::FVector& value);
	void TextVectorColored(const char* label, const SDK::FVector& value);


	void TextRotator(const char* label, const SDK::FRotator& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative);
	void TextRotator(const char* label, const SDK::FRotator& value);
	void TextRotatorColored(const char* label, const SDK::FRotator& value);


	void TextHint(const char* hint);


	void ReadOnlyInputText(const char* label, const char* text, const bool& showCopyButton);


	enum E_ObjectFilterMode
	{
		ClassName,
		ObjectName,
		All
	};
	void ObjectFilterModeComboBox(const char* label, E_ObjectFilterMode* v);


	/*
	* @brief Using pre-determined table, converts an ImGui key to the corresponding WinAPI virtual-key code.
	* @param key - ImGui key to be converted.
	* @return The corresponding WinAPI virtual-key code, or 0 if unsupported.
	*/
	static int ImGuiKey_ToWinAPI(const ImGuiKey& key);
	/*
	* @brief Using pre-determined table, returns a human-readable name for a given ImGui key.
	* @param key - ImGui key to get the name of.
	* @return The key name as a string.
	*/
	static const char* ImGuiKey_GetName(const ImGuiKey& key);


	struct KeyBinding
	{
		ImGuiKey key = ImGuiKey_None;
		bool isDetermined = true;
		bool isInUse = false;
	};
	/*
	* @brief Renders a key binding input control in ImGui.
	* 
	* Displays a button with the current binding state and allows the user
	* to assign or unbind a key interactively.
	* 
	* @param label - label text to display (may contain "##" to hide ID).
	* @param binding - pointer to key binding structure.
	* @return 'True' if the binding was changed; otherwise 'False'
	*/
	bool KeyBindingInput(const char* label, KeyBinding* binding);
	bool IsKeyBindingPressed(KeyBinding* binding, const bool& waitForRelease = true);
	bool IsKeyBindingDown(KeyBinding* binding);
	bool IsKeyBindingReleased(KeyBinding* binding);


	/*
	* @brief Sets the font scale to the specified value.
	* @param fontScale - scale factor.
	*/
	static void SetFontScale(const float& fontScale)
	{
		SetWindowFontScale(fontScale);
	}
	/*
	* @brief Sets the font scale to 0.5x.
	*/
	static void SetFontTiny()
	{
		SetFontScale(0.5f);
	}
	/*
	* @brief Sets the font scale to 0.75x.
	*/
	static void SetFontLittle()
	{
		SetFontScale(0.75f);
	}
	/*
	* @brief Sets the font scale to 0.9x.
	*/
	static void SetFontSmall()
	{
		SetFontScale(0.9f);
	}
	/*
	* @brief Sets the font scale to 1.0x.
	*/
	static void SetFontRegular()
	{
		SetFontScale(1.0f);
	}
	/*
	* @brief Sets the font scale to 1.1x.
	*/
	static void SetFontBig()
	{
		SetFontScale(1.1f);
	}
	/*
	* @brief Sets the font scale to 1.25x.
	*/
	static void SetFontLarge()
	{
		SetFontScale(1.25f);
	}
	/*
	* @brief Sets the font scale to 1.5x.
	*/
	static void SetFontTitle()
	{
		SetFontScale(1.5f);
	}




	/*
	* @brief New Line + Separator + New Line.
	*/
	static void CategorySeparator()
	{
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();
	}


	/*
	* @brief Prints pre-determined number of spaces to expand menu horizontally.
	*/
	static void MenuSpacer()
	{
		static const char* menuSpacer = "                                                                                               ";
		ImGui::TextUnformatted(menuSpacer, menuSpacer + 95);
	}
};






class GUI
{
private:
	static inline HANDLE windowThread = nullptr;
public:
	static HANDLE GetWindowThread()
	{
		return windowThread;
	}
	static bool StartWindowThread();


private:
	static inline bool isTitleInFocus = false;
public:
	static bool GetIsTitleInFocus()
	{
		return isTitleInFocus;
	}
	static void SetIsTitleInFocus(const bool& newIsInFocus)
	{
		isTitleInFocus = newIsInFocus;
	}


private:
	static inline bool isMenuActive = false;
public:
	static bool GetIsMenuActive()
	{
		return isMenuActive;
	}
	static void SetIsMenuActive(const bool& newIsActive)
	{
		isMenuActive = newIsActive;
	}
	static void ToggleIsMenuActive()
	{
		isMenuActive = !isMenuActive;
	}


#ifdef _DEBUG
private:
	static inline int8_t menuDebugLevel = 0;
public:
	static int8_t GetMenuDebugLevel()
	{
		return menuDebugLevel;
	}
	static bool GetIsMenuDebugEnabled()
	{
		return menuDebugLevel > 0;
	}
	static bool GetIsMenuDebugDetailed()
	{
		return menuDebugLevel == 2;
	}
	static void SetMenuDebugLevel(const int8_t& newMenuDebugLevel)
	{
		menuDebugLevel = newMenuDebugLevel;
	}
	static void SwitchMenuDebugLevel()
	{
		int8_t newMenuDebugLevel = menuDebugLevel + 1;
		if (newMenuDebugLevel > 2)
			menuDebugLevel = 0;
		else
			menuDebugLevel = newMenuDebugLevel;
	}
#endif




public:
	/*
	* @brief Initializes the GUI system. Should be called to start ImGui and create the menu.
	* @param applicationModule - Handle of the current (this) DLL module.
	*/
	static void Init(const HMODULE& applicationModule);
#ifdef WAIT_FOR_TITLE_INIT
	/*
	* @brief Initializes the GUI system once general Unreal Engine subsystems are up and running. Should be called to start ImGui and create the menu.
	* @param applicationModule - Handle of the current (this) DLL module.
	*/
	static void InitOnTitleInitialized(const HMODULE& applicationModule);
#endif


	/*
	* @brief Renders frame of GUI elements.
	* 
	* Called once per frame by DirectWindow class (on each ImGui::NewFrame())
	* to draw application-specific ImGui controls and windows.
	*/
	static void Draw();




public:
	enum class E_Sound
	{
		BUTTON_PRESS,
		BUTTON_CANCEL,
		ACTION_SUCCESS,
		ACTION_ERROR
	};
	static void PlayUISound(const E_Sound& soundToPlay);
	static void PlayActionSound(const bool& wasSuccessfull)
	{
		PlayUISound(wasSuccessfull ? E_Sound::ACTION_SUCCESS : E_Sound::ACTION_ERROR);
	}






	class SharedFunctions
	{
	public:
		static void Ghost();
		static void Fly();
		static void Walk();


	public:
		static void Jump();


	public:
		static void Launch();
		static void Dash();
	};
};






class DebugDraw
{
public:
#ifdef COLLISION_VISUALIZER
	static void DrawBodySetup(SDK::UBodySetup* bodySetup, const Unreal::Transform& componentTransform, const uint32_t& drawColor, const float& drawThickness);
	static void DrawVolume(SDK::AVolume* volume, const uint32_t& drawColor, const float& drawThickness);

	static void DrawStaticMeshComponent(SDK::UStaticMeshComponent* staticMeshComponent, const uint32_t& drawColor, const float& drawThickness);
	static void DrawInstancedStaticMeshComponent(SDK::UInstancedStaticMeshComponent* instancedStaticMeshComponent, const uint32_t& drawColor, const float& drawThickness);

	static void DrawSkeletalMeshComponent(SDK::USkeletalMeshComponent* skeletalMeshComponent, const bool& drawAllSockets, const uint32_t& drawColor, const float& drawThickness);

	static void DrawCapsuleComponent(SDK::UCapsuleComponent* capsuleComponent, const uint32_t& drawColor, const float& drawThickness);
	static void DrawSphereComponent(SDK::USphereComponent* sphereComponent, const uint32_t& drawColor, const float& drawThickness);
	static void DrawBoxComponent(SDK::UBoxComponent* boxComponent, const uint32_t& drawColor, const float& drawThickness);
	static void DrawSplineComponent(SDK::USplineComponent* splineComponent, const uint32_t& drawColor, const float& drawThickness);
#endif
};






namespace Features
{
	class Config
	{
	private:
		template <typename T>
		static void ReadFeatureFromConfig(ConfigInstance* featuresConfig, const std::string& entryName, T* featureValue);

	public:
		static void Load();
		static void Save();
	};




	class Menu
	{
	public:
		static inline bool enableSound = true;

		static inline bool autoConstructConsole = false;
		static inline bool enableConsoleOutput = true;
	};




	class Debug
	{
	public:
		static inline bool enabled;

		static inline double lastUpdateTime;

		static inline bool autoUpdate = false;
		static inline float autoUpdateDelay = 0.25f;

		static inline Unreal::Engine::DataStructure engine;

		static inline Unreal::GameInstance::DataStructure gameInstance;

		static inline Unreal::GameMode::DataStructure gameMode;

		static inline Unreal::PlayerController::DataStructure playerController;

		static inline Unreal::World::DataStructure world;
		static inline const size_t streamingLevelsFilterBufferSize = 255;
		static inline char streamingLevelsFilterBuffer[streamingLevelsFilterBufferSize] = {};
		static inline bool streamingLevelsFilterCaseSensitive = true;
		static inline bool streamingLevelsEditorColors = false;

		static inline bool wasProjectNameObtained;
		static inline std::string projectName;

		static inline bool wasProjectPlatformObtained;
		static inline std::string projectPlatform;

		static inline bool wasProjectEngineVersionObtained;
		static inline std::string projectEngineVersion;

		static inline bool wasUsernameObtained;
		static inline std::string username;

		static inline bool wasCommandLineObtained;
		static inline std::string commandLine;


		static void Update();
		static void ThreadSafeUpdate();
	};




#ifdef SOFT_PATH
	class ActorSpawn
	{
	public:
		/* Allocate large buffer to account for combined paths (e.g: "/Game/Blueprints/Watermelon.Watermelon_C | /Game/Blueprints/Cookie.Cookie_C") */
		static inline const size_t actorPathBufferSize = 2048;
		static inline char actorPathBuffer[actorPathBufferSize] = {};

		static inline float location[3];
		static inline bool useCharacterLocation = true;
		static inline float rotation[3];
		static inline bool useCharacterRotation = true;
		static inline float scale[3] = { 1.0f, 1.0f, 1.0f };

		static inline std::vector<SDK::FString> loadedClasses;
	};
#endif




	class ActorsList
	{
	public:
		static inline const size_t filterBufferSize = 255;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = true;
		static inline ImGui::E_ObjectFilterMode filterMode = ImGui::E_ObjectFilterMode::All;
		static inline bool filterCheckValidness = false;
		static inline float filterDistance = 0.0f;

		static inline float color_Valid[4] = { 0.2f, 0.8f, 0.3f, 1.0f };
		static inline float color_Invalid[4] = { 0.8f, 0.3f, 0.2f, 1.0f };

		static inline std::vector<Unreal::Actor::DataStructure> actors;
		static inline std::vector<Unreal::Actor::DataStructure> filteredActors;

		static inline const size_t componentsFilterBufferSize = 255;
		static inline char componentsFilterBuffer[componentsFilterBufferSize] = {};
		static inline bool componentsFilterCaseSensitive = true;
		static inline ImGui::E_ObjectFilterMode componentsFilterMode = ImGui::E_ObjectFilterMode::All;


		static void Update();
		static void Filter();
	};




	class WidgetsList
	{
	public:
		static inline const size_t filterBufferSize = 255;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = true;
		static inline ImGui::E_ObjectFilterMode filterMode = ImGui::E_ObjectFilterMode::All;
		static inline bool filterTopLevelOnly = true;

		static inline std::vector<Unreal::UserWidget::DataStructure> widgets;
		static inline std::vector<Unreal::UserWidget::DataStructure> filteredWidgets;

		static inline std::vector<std::pair<SDK::UUserWidget*, SDK::ESlateVisibility>> storedWidgetsVisibility;


		static void Update();
		static void Filter();
	};




	class ObjectsList
	{
	public:
		static inline const size_t filterBufferSize = 255;
		static inline char filterBuffer[filterBufferSize] = {};
		static inline bool filterCaseSensitive = true;
		static inline ImGui::E_ObjectFilterMode filterMode = ImGui::E_ObjectFilterMode::All;

		static inline std::vector<Unreal::Object::DataStructure> objects;
		static inline std::vector<Unreal::Object::DataStructure> filteredObjects;


		static void Update();
		static void Filter();
	};




#ifdef ACTOR_TRACE
	class ActorTrace
	{
	public:
		static inline bool enabled = false;
		static inline bool showOnScreen = true;
		static inline bool showLineTrace = true;

		static inline SDK::FVector traceStartLocation;
		static inline SDK::FVector traceEndLocation;
		static inline float traceColor[4] = { 0.118f, 1.0f, 0.0f, 0.5f };
		static inline float traceThickness = 3.5f;
		static inline float traceLength = 2048.0f;

		static inline bool traceCast; // When set to 'True', indicates that user have casted a ray; would render a dummy { 0.0, 0.0 } - { 0.0, 0.0 } line otherwise.
		static inline bool traceHit;

#ifdef UE5
		static inline Unreal::Object::DataStructure object;
#else
		static inline Unreal::Actor::DataStructure actor;
#endif


		static bool Trace();
	};
#endif




#ifdef ACTORS_TRACKING
	class ActorsTracker
	{
	public:
		static inline bool enabled = false;
	};
#endif




#ifdef COLLISION_VISUALIZER
	class CollisionVisualizer
	{
	public:
		static inline bool enabled = false;


		static inline float opacity = 0.5f;


		/* Blueish - Collision/Physics related. */
		static inline float color_StaticMesh[4] = { 0.0f, 0.5f, 1.0f, opacity };
		static inline float color_Primitive[4] = { 0.0f, 0.8f, 1.0f, opacity };
		static inline float color_PhysicsVolume[4] = { 0.3f, 0.25f, 0.85f, opacity };

		/* Reddish - Damage/Restriction related. */
		static inline float color_BlockingVolume[4] = { 1.0f, 0.25f, 0.2f, opacity };

		/* Greenish - Event related (e.g: trigger). */
		static inline float color_TriggerVolume[4] = { 0.3f, 1.0f, 0.3f, opacity };

		/* Pinkish - Post Processing. */
		static inline float color_PostProcessVolume[4] = { 0.8f, 0.2f, 0.8f, opacity };

		/* White - Unknown/Other. */
		static inline float color_Other[4] = { 1.0f, 1.0f, 1.0f, opacity };


		static inline float thickness = 0.5f;


		static void Draw();
		static void ThreadSafeDraw();
	};
#endif




#ifdef SOFT_PATH
	class PawnAnimation
	{
	public:
		static inline const size_t animationMontagePathBufferSize = 255;
		static inline char animationMontagePathBuffer[animationMontagePathBufferSize] = {};
		static inline float animationMontageStartAt = 0.0f;
		static inline float animationMontagePlayRate = 1.0f;
		static inline bool animationMontageStopAllMontages = true;

		static inline const size_t animationPathBufferSize = 255;
		static inline char animationPathBuffer[animationPathBufferSize] = {};
		static inline bool animationLooping = false;
	};




	class WidgetConstruct
	{
	public:
		/* Allocate large buffer to account for combined paths (e.g: "/Game/Blueprints/Watermelon.Watermelon_C | /Game/Blueprints/Cookie.Cookie_C") */
		static inline const size_t widgetPathBufferSize = 2048;
		static inline char widgetPathBuffer[widgetPathBufferSize] = {};

		static inline int32_t zOrder = 0;
	};
#endif




#ifdef SOFT_PATH
	class LoadLevelInstance
	{
	public:
		/* Allocate large buffer to account for combined paths (e.g: "/Game/OpenWorld/Tile_X2Y8.Tile_X2Y8 | /Game/OpenWorld/Tile_X4Y6.Tile_X4Y6") */
		static inline const size_t levelPathBufferSize = 2048;
		static inline char levelPathBuffer[levelPathBufferSize] = {};

		static inline float locationOffset[3];
		static inline float rotationOffset[3];
	};


#ifdef LEVEL_SEQUENCE
	class PlayLevelSequence
	{
	public:
		/* Allocate large buffer to account for combined paths (e.g: "/Game/OpenWorld/Sequences/LS_TowerExplosion.LS_TowerExplosion | /Game/OpenWorld/Sequences/LS_CrowdRunning.LS_CrowdRunning") */
		static inline const size_t levelSequencePathBufferSize = 2048;
		static inline char levelSequencePathBuffer[levelSequencePathBufferSize] = {};

		static inline float startTime = 0.0f;
		static inline float playRate = 1.0f;
		static inline int32_t loopCount = 1;
	};
#endif
#endif




	class CharacterMovement
	{
	public:
		static void Ghost();
		static void Fly();
		static void Walk();


		static void Jump();


		static inline float launchVelocity[3] = { 0.0f, 0.0f, 1325.0f };
		static void Launch();


		static inline double dashStrength = 3375.0;
		static void Dash();
	};




	class Camera
	{
	public:
		static inline float fadeFromAlpha = 0.0f;
		static inline float fadeToAlpha = 1.0f;
		static inline float fadeDuration = 2.5f;
		static inline float fadeColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		static inline bool fadeAudio = false;
		static inline bool fadePersistent = true;


		static void StartFade();
		static void StopFade();
	};




	class DirectionalMovement
	{
	public:
		static inline bool enabled = false;

		static inline bool omniMovement = true;
		static inline bool isUpMovementExpected = false;
		static inline bool isDownMovementExpected = false;

		static inline float step = 50.0;
		static inline float delay = 0.05;


	private:
		static inline HANDLE thread = nullptr;
		static void Worker();
	public:
		static void Enable();
		static void Disable();
	};




#ifdef FREE_CAMERA
	class FreeCamera
	{
	public:
		static inline SDK::ACameraActor* cameraReference;
		static inline SDK::AActor* lastViewTarget;

		static inline float cameraMovementStep = 3.0f;
		static inline float cameraRotationStep = 0.25f;


		static bool IsEnabled();
		static bool Enable();
		static bool Disable();
		static void Toggle();

		static bool Move(const float& forwardStep, const float& rightStep, const float& upStep);
		static bool Rotate(const float& horizontalStep, const float& verticalStep);

		static bool TeleportCameraToPlayer();
		static bool TeleportPlayerToCamera();
	};
#endif




	class Console
	{
	public:
		/* Allocate large buffer to account for combined console commands (e.g: "stat fps | stat unit") */
		static inline const size_t consoleBufferSize = 2048;
		static inline char consoleBuffer[consoleBufferSize] = {};
	};
};






namespace Inputs
{
	class Config
	{
	private:
		static void ReadKeyBindingFromConfig(ConfigInstance* keybindingsConfig, const std::string& entryName, ImGui::KeyBinding* keyBinding);

	public:
		static void Load();
		static void Save();
	};




	class Keybindings
	{
	public:
		static inline ImGui::KeyBinding general_MenuOpenClose{ ImGuiKey_Insert };

#ifdef ACTOR_TRACE
		static inline ImGui::KeyBinding debug_ActorTrace;
#endif
		static inline ImGui::KeyBinding debug_ActorsListUpdate;
#ifdef ACTORS_TRACKING
		static inline ImGui::KeyBinding debug_ActorsListTracking;
#endif
#ifdef COLLISION_VISUALIZER
		static inline ImGui::KeyBinding debug_ActorsListCollisionDraw;
#endif

		static inline ImGui::KeyBinding characterMovement_Ghost;
		static inline ImGui::KeyBinding characterMovement_Fly;
		static inline ImGui::KeyBinding characterMovement_Walk;
		static inline ImGui::KeyBinding characterMovement_Jump;
		static inline ImGui::KeyBinding characterMovement_Launch;
		static inline ImGui::KeyBinding characterMovement_Dash;

		static inline ImGui::KeyBinding characterOmniMovement_Up;
		static inline ImGui::KeyBinding characterOmniMovement_Down;

		static inline ImGui::KeyBinding characterCamera_StartFade;
		static inline ImGui::KeyBinding characterCamera_StopFade;

#ifdef FREE_CAMERA
		static inline ImGui::KeyBinding freeCamera_TeleportCameraToPlayer;
		static inline ImGui::KeyBinding freeCamera_Toggle;
		static inline ImGui::KeyBinding freeCamera_TeleportPlayerToCamera;
		static inline ImGui::KeyBinding freeCamera_MoveForward{ ImGuiKey_W };
		static inline ImGui::KeyBinding freeCamera_MoveBackward{ ImGuiKey_S };
		static inline ImGui::KeyBinding freeCamera_MoveLeft{ ImGuiKey_A };
		static inline ImGui::KeyBinding freeCamera_MoveRight{ ImGuiKey_D };
		static inline ImGui::KeyBinding freeCamera_MoveUp{ ImGuiKey_E };
		static inline ImGui::KeyBinding freeCamera_MoveDown{ ImGuiKey_Q };
		static inline ImGui::KeyBinding freeCamera_RotateUp{ ImGuiKey_UpArrow };
		static inline ImGui::KeyBinding freeCamera_RotateDown{ ImGuiKey_DownArrow };
		static inline ImGui::KeyBinding freeCamera_RotateLeft{ ImGuiKey_LeftArrow };
		static inline ImGui::KeyBinding freeCamera_RotateRight{ ImGuiKey_RightArrow };
#endif


	private:
		static inline HANDLE thread = nullptr;
		static inline bool isProcessing = false;
		static void Worker();
	public:
		static void EnableProcessing();
		static void DisableProcessing();
	};
};