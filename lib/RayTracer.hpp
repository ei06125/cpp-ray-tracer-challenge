#pragma once

/// @section Math
#include "RayTracer/Math/Constants.hpp"
#include "RayTracer/Math/Matrix.hpp"
#include "RayTracer/Math/Transformations.hpp"
#include "RayTracer/Math/Tuple.hpp"

/// @section Rendering
#include "RayTracer/Rendering/Canvas.hpp"

/// @subsection Cameras
#include "RayTracer/Rendering/Cameras/Camera.hpp"

/// @subsection Lighting
#include "RayTracer/Rendering/Lighting/Computations.hpp"
#include "RayTracer/Rendering/Lighting/Intersection.hpp"
#include "RayTracer/Rendering/Lighting/Light.hpp"
#include "RayTracer/Rendering/Lighting/Ray.hpp"

/// @subsection Materials
#include "RayTracer/Rendering/Materials/Material.hpp"

/// @subsection Primitives
#include "RayTracer/Rendering/Primitives/Plane.hpp"
#include "RayTracer/Rendering/Primitives/Shape.hpp"
#include "RayTracer/Rendering/Primitives/Sphere.hpp"

/// @subsection Scene
#include "RayTracer/Rendering/Scene/World.hpp"

/// @section Utils
#include "RayTracer/Utils/PPMFile.hpp"
#include "RayTracer/Utils/Print.hpp"
