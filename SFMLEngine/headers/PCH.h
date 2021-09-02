#pragma once

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

#include "box2d/box2d.h"

#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

#include "Engine.h"
#include "Scene.h"
#include "Vec2.h"
#include "ResourceManager.h"
#include "Keyboard.h"
#include "ParticleSystem.h"
#include "ParticleFountain.h"
#include "Tilemap.h"
#include "LifeCycleManager.h"

#include "Components/Component.h"
#include "Components/Transform.h"
#include "Components/RigidBody2D.h"
#include "Components/BoxCollider.h"
#include "Components/CircleCollider.h"
#include "Components/SpriteRenderer.h"
#include "Components/Animation.h"
#include "Components/Animator.h"
#include "Components/Controller.h"