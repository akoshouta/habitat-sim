// Copyright (c) Facebook, Inc. and its affiliates.
// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#include "Attributes.h"

namespace esp {
namespace assets {

//----------------------------------------//
//  Derived attribute implementations
//----------------------------------------//

AbstractPhysicsAttributes::AbstractPhysicsAttributes(
    const std::string& originHandle)
    : Configuration() {
  setOriginHandle(originHandle);
  setFrictionCoefficient(0.5);
  setRestitutionCoefficient(0.1);
  setRenderAssetHandle("");
  setCollisionAssetHandle("");
}  // AbstractPhysicsAttributes ctor

/**
 * AbstractPhysicsAttributes is abstract; virtual destructor deleted;
 * definition required so instancing class can destroy base  REMOVED FOR PYBIND
 * COMPATIBILITY TODO: Find a pybind-friendly way to implement this
 *
 * AbstractPhysicsAttributes::~AbstractPhysicsAttributes() {}
 */

PhysicsObjectAttributes::PhysicsObjectAttributes(
    const std::string& originHandle)
    : AbstractPhysicsAttributes(originHandle) {
  // fill necessary attribute defaults
  setMass(1.0);
  setMargin(0.04);
  setScale({1.0, 1.0, 1.0});
  setCOM({0, 0, 0});
  setInertia({0, 0, 0});
  setLinearDamping(0.2);
  setAngularDamping(0.2);
  // default collisions will be mesh for physics objects
  // primitive-based objects do not currently support mesh collisions, however,
  // due to issues with how non-triangle meshes (i.e. wireframes) are handled in
  // @ref GenericMeshData::setMeshData
  setUseMeshCollision(true);

  setBoundingBoxCollisions(false);
  setJoinCollisionMeshes(true);
  setRequiresLighting(true);
  setIsVisible(true);
  setIsCollidable(true);
}  // PhysicsObjectAttributes ctor

PhysicsSceneAttributes::PhysicsSceneAttributes(const std::string& originHandle)
    : AbstractPhysicsAttributes(originHandle) {
  setGravity({0, -9.8, 0});
  // TODO do these defaults need to be maintained here?
  setFrictionCoefficient(0.4);
  setRestitutionCoefficient(0.05);
}  // PhysicsSceneAttributes ctor

PhysicsManagerAttributes::PhysicsManagerAttributes(
    const std::string& originHandle)
    : Configuration() {
  setSimulator("none");
  setOriginHandle(originHandle);
  setTimestep(0.01);
  setMaxSubsteps(10);
}  // PhysicsManagerAttributes ctor

/**
 * AbstractPrimitiveAttributes is abstract; virtual destructor deleted;
 * definition required so instancing class can destroy base  REMOVED FOR PYBIND
 * COMPATIBILITY TODO: Find a pybind-friendly way to implement this
 *
 * AbstractPrimitiveAttributes::~AbstractPrimitiveAttributes() {}
 */
CapsulePrimitiveAttributes::CapsulePrimitiveAttributes(
    bool isWireframe,
    const std::string& primObjType)
    : AbstractPrimitiveAttributes(isWireframe, primObjType) {
  setCylinderRings(1);
  if (!isWireframe) {  // solid
    setHemisphereRings(4);
    setNumSegments(12);
    setHalfLength(0.75);
  } else {  // wireframe
    setHemisphereRings(8);
    setNumSegments(16);
    setHalfLength(1.0);
  }
  buildOriginHandle();  // build handle based on config
}  // PhysicsCapsulePrimAttributes

ConePrimitiveAttributes::ConePrimitiveAttributes(bool isWireframe,
                                                 const std::string& primObjType)
    : AbstractPrimitiveAttributes(isWireframe, primObjType) {
  setHalfLength(1.25);

  if (!isWireframe) {  // solid
    setNumRings(1);
    setNumSegments(12);
    setCapEnd(true);
  } else {  // wireframe
    setNumSegments(32);
  }
  buildOriginHandle();  // build handle based on config
}  // PhysicsConePrimAttributes

CylinderPrimitiveAttributes::CylinderPrimitiveAttributes(
    bool isWireframe,
    const std::string& primObjType)
    : AbstractPrimitiveAttributes(isWireframe, primObjType) {
  setNumRings(1);
  setHalfLength(1.0);

  if (!isWireframe) {  // solid
    setNumSegments(12);
    setCapEnds(true);
  } else {  // wireframe
    setNumSegments(32);
  }
  buildOriginHandle();  // build handle based on config
}  // PhysicsCylinderPrimAttributes

UVSpherePrimitiveAttributes::UVSpherePrimitiveAttributes(
    bool isWireframe,
    const std::string& primObjType)
    : AbstractPrimitiveAttributes(isWireframe, primObjType) {
  if (!isWireframe) {  // solid
    setNumRings(8);
    setNumSegments(16);
  } else {  // wireframe
    setNumRings(16);
    setNumSegments(32);
  }
  buildOriginHandle();  // build handle based on config
}  // PhysicsUVSpherePrimAttributes

}  // namespace assets
}  // namespace esp
