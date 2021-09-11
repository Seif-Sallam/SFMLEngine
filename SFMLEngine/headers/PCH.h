#pragma once
// Including STLs
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <vector>
#include <array>
#include <iterator>
#include <climits>
#include <exception>
#include <map>
#include <unordered_map>
#include <memory>
#include <random>

// Including Physics Related Libraries (They are all in box2d.h)
#include "box2d/box2d.h"

// Include SFML
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

// Including Engine related files
#include "Engine.h"
#include "Scene.h"
#include "FPSCounter.h"
#include "ResourceManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "ParticleSystem.h"
#include "ParticleFountain.h"
#include "Tilemap.h"
#include "LifeCycleManager.h"

// Including Utlities
#include "Vec2.h"

// Including Components
#include "Components/Component.h"
#include "Components/Transform.h"
#include "Components/RigidBody2D.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"
#include "Components/SpriteRenderer.h"
#include "Components/Animation.h"
#include "Components/Animator.h"
#include "Components/Controller.h"
#include "Components/Highlightable.h"

// UI
#include "UI/Canvas.h"
#include "UI/UIElement.h"
#include "UI/Textbox.h"