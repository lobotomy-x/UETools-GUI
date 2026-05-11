#pragma once
#include "SDK/Engine_classes.hpp"






/* Forward declaration of Unreal.h struct. */
namespace Unreal { struct Transform; }




class Math
{
public:
	static SDK::FVector Vector_Add(const SDK::FVector& A, const SDK::FVector& B);
	static SDK::FVector Vector_Multiply(const SDK::FVector& A, const float& B);
	static SDK::FVector Vector_Normal(const SDK::FVector& vector, const float& tolerance = 1.0E-8F); // sqrt(1e-8) = 1e-4 = 0.0001f.
	static SDK::FVector Vector_Rotate(const SDK::FVector& vector, const SDK::FQuat& quat);
	static float Vector_Distance(const SDK::FVector& A, const SDK::FVector& B);
	static float Vector_Dot(const SDK::FVector& A, const SDK::FVector& B);
	static SDK::FVector Vector_Cross(const SDK::FVector& A, const SDK::FVector& B);
	static SDK::FVector Vector_LocalToWorld(const Unreal::Transform& unrealTransform, const SDK::FVector& vector);


	static SDK::FRotator Quat_ToRotator(const SDK::FQuat& quat);
	static SDK::FQuat Rotator_ToQuat(const SDK::FRotator& rotator);
	static SDK::FVector Rotator_ForwardVector(const SDK::FRotator& rotator);
	static SDK::FVector Rotator_RightVector(const SDK::FRotator& rotator);
	static SDK::FVector Rotator_UpVector(const SDK::FRotator& rotator);


	static Unreal::Transform F_ToUnrealTransform(const SDK::FTransform& fTransform);
	static SDK::FTransform Unreal_ToFTransform(const Unreal::Transform& unrealTransform);


	static uint32_t ColorFloat4_ToU32(const float color[4]);


	static uint32_t Seconds_ToMilliseconds(const double& seconds);


	static float Unit_ToMetre(const float& units);
	static float Unit_ToInch(const float& units);

	static float Metre_ToUnit(const float& metres);
	static float Metre_ToInch(const float& metres);

	static float Inch_ToUnit(const float& inches);
	static float Inch_ToMetre(const float& inches);


	static inline const float PI   = 3.14f;
	static inline const float DTR  = PI / 180.0f; // Degrees-to-radians factor.
	static inline const float RTD  = 180.0f / PI; // Radians-to-degrees factor.
	static inline const float TINY = 1e-8f;		  // Small epsilon to avoid divide-by-zero in normalization.
};

