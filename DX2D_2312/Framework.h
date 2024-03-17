﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#define WIN_START_X 100
#define WIN_START_Y 0

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define CENTER_X (SCREEN_WIDTH * 0.5f)
#define CENTER_Y (SCREEN_HEIGHT * 0.5f)

#define CENTER Vector2(CENTER_X, CENTER_Y)

#define FOR(n) for(int i = 0 ; i < n ; i++)

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define SCENE SceneManager::Get()
#define KEY Keyboard::Get()
#define DELTA Timer::Get()->GetElapsedTime()
#define CAM Environment::Get()->GetMainCamera()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <algorithm>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//DirectXTex
#include <DirectXTex/DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")

//FMOD
#include <FMOD/fmod.h>
#pragma comment(lib, "fmod_vc.lib")

//ImGui
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_dx11.h>
#include <ImGui/imgui_impl_win32.h>

#pragma comment(lib, "ImGui.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;

//Framework Header
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/Math.h"

#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Utility.h"

#include "Framework/Device/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/Mesh.h"

#include "Framework/Collision/Collider.h"
#include "Framework/Collision/RectCollider.h"
#include "Framework/Collision/CircleCollider.h"

#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/ObjectManager.h"
#include "Objects/Basic/PoolingManager.h"
#include "Objects/Basic/Quad.h"

#include "Objects/UI/ProgressBar.h"

#include "Objects/ShootingGame/ShootingDataManager.h"
#include "Objects/ShootingGame/Skill/Skill.h"
#include "Objects/ShootingGame/Skill/BaseSkill.h"
#include "Objects/ShootingGame/Skill/WheelSkill.h"
#include "Objects/ShootingGame/Skill/Bullet.h"
#include "Objects/ShootingGame/Skill/BaseBullet.h"
#include "Objects/ShootingGame/Skill/WheelBullet.h"
#include "Objects/ShootingGame/Skill/BulletManager.h"
#include "Objects/ShootingGame/Enemy/Enemy.h"
#include "Objects/ShootingGame/Enemy/RangeEnemy.h"
#include "Objects/ShootingGame/Enemy/DashEnemy.h"
#include "Objects/ShootingGame/Enemy/EnemyManager.h"
#include "Objects/ShootingGame/Plane.h"
#include "Objects/ShootingGame/Background.h"

//Scene Header
#include "Scenes/Scene.h"
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"

extern HWND hWnd;
extern Vector2 mousePos;