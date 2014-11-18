#pragma once

#pragma warning(disable:4005)
#pragma warning(disable:4094)
#pragma warning(disable:4127)
#pragma warning(disable:4239)
#pragma warning(disable:4267)
#pragma warning(disable:4311)
#pragma warning(disable:4786)
#pragma warning(disable:4819)
#pragma warning(disable:4996)


// ���w
#include "Math/Math.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "Math/Quaternion.h"
#include "Math/Transformation.h"
// ������̐U�镑��������I�u�W�F�N�g
#include "Graphics/View/ViewBehavior.h"
#include "Graphics/View/Camera.h"
// �`��
#include "Graphics/Texture.h"
#include "Graphics/Vertex.h"
#include "Graphics/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Animation.h"
#include "Graphics/Renderer/GraphicBehavior.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/Particle/Particle.h"
#include "Graphics/Shader/Lambert/ShaderLambert.h"
#include "Graphics/Shader/Phong/ShaderPhong.h"
#include "Graphics/Shader/HalfLambert/ShaderHalfLambert.h"
#include "Graphics/Shader/Toon/ShaderToon.h"
#include "Graphics/GraphicsManager.h"
#include "Graphics/Text.h"
// �`��
#include "Graphics/Renderer/Sprite.h"
#include "Graphics/Renderer/PointSprite.h"
#include "Graphics/Renderer/GraphicalShape/GraphicalPlane.h"
#include "Graphics/Renderer/ModelRenderer.h"
#include "Graphics/Renderer/Layer.h"
// ����
#include "Phisycs/BoundingVolume.h"
#include "Phisycs/Collision.h"
#include "Phisycs/TreeObject.h"
#include "Phisycs/QuadTree.h"
// �V�X�e��
#include "System/Debug.h"
#include "System/FrameRateCounter.h"
#include "System/Timer.h"
#include "System/Command.h"
#include "System/Counter.h"
// ���p
#include "Support/wsb_xml.h"
#include "Support/JoyPadManager.h"
#include "Support/sound.h"
#include "Support/sound_manager.h"
// �g��
#include "Extension.h"