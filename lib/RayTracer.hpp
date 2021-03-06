#pragma once
#include "RayTracerPCH.hpp"

/// ===========================================================================
/// @section Math
#include "RayTracer/Math/Constants.hpp"
#include "RayTracer/Math/Matrix.hpp"
#include "RayTracer/Math/Transformations.hpp"
#include "RayTracer/Math/Tuple.hpp"

/// ===========================================================================
/// @section Profiling
#include "RayTracer/Profiling/TrackCalls.hpp"
#include "RayTracer/Profiling/TrackNew.hpp"
#include "RayTracer/Profiling/TrackTime.hpp"

/// ===========================================================================
/// @section Rendering
#include "RayTracer/Rendering/Canvas.hpp"
#include "RayTracer/Rendering/Color.hpp"

/// ---------------------------------------------------------------------------
/// @subsection Cameras
#include "RayTracer/Rendering/Cameras/Camera.hpp"

/// ---------------------------------------------------------------------------
/// @subsection Lighting
#include "RayTracer/Rendering/Lighting/Computations.hpp"
#include "RayTracer/Rendering/Lighting/Intersection.hpp"
#include "RayTracer/Rendering/Lighting/Light.hpp"
#include "RayTracer/Rendering/Lighting/Ray.hpp"

/// ---------------------------------------------------------------------------
/// @subsection Materials
#include "RayTracer/Rendering/Materials/Material.hpp"

/// ---------------------------------------------------------------------------
/// @subsection Primitives
#include "RayTracer/Rendering/Primitives/CSG.hpp"
#include "RayTracer/Rendering/Primitives/Cone.hpp"
#include "RayTracer/Rendering/Primitives/Cube.hpp"
#include "RayTracer/Rendering/Primitives/Cylinder.hpp"
#include "RayTracer/Rendering/Primitives/Group.hpp"
#include "RayTracer/Rendering/Primitives/Plane.hpp"
#include "RayTracer/Rendering/Primitives/Shape.hpp"
#include "RayTracer/Rendering/Primitives/SmoothTriangle.hpp"
#include "RayTracer/Rendering/Primitives/Sphere.hpp"
#include "RayTracer/Rendering/Primitives/Triangle.hpp"

/// ---------------------------------------------------------------------------
/// @subsection Scene
#include "RayTracer/Rendering/Scene/World.hpp"

/// ---------------------------------------------------------------------------
/// @subsection Parsers
#include "RayTracer/Rendering/Parsers/OBJParser.hpp"

/// ---------------------------------------------------------------------------
/// @subsection Patterns
#include "RayTracer/Rendering/Patterns/BlendedPattern.hpp"
#include "RayTracer/Rendering/Patterns/CheckersPattern.hpp"
#include "RayTracer/Rendering/Patterns/GradientPattern.hpp"
#include "RayTracer/Rendering/Patterns/NestedPattern.hpp"
#include "RayTracer/Rendering/Patterns/Pattern.hpp"
#include "RayTracer/Rendering/Patterns/PerturbedPattern.hpp"
#include "RayTracer/Rendering/Patterns/RadialGradientPattern.hpp"
#include "RayTracer/Rendering/Patterns/RingPattern.hpp"
#include "RayTracer/Rendering/Patterns/SolidColorPattern.hpp"
#include "RayTracer/Rendering/Patterns/StripePattern.hpp"

/// ===========================================================================
/// @section Utils
#include "RayTracer/Utils/OBJFile.hpp" // TODO: move to FileSystem
#include "RayTracer/Utils/PPMFile.hpp" // TODO: move to FileSystem
#include "RayTracer/Utils/Print.hpp"
