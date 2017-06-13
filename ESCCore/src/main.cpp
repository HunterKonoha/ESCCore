#include <Siv3D.hpp>
#include "Entity/Entity.h"
#include "Entity/detail/EntityManager.h"
#include "Component/Render/ShapeRender.h"
#include "Component/Render/TextRender.h"
#include "Component/Render/ImageRender.h"
#include "Component/Update/VariableUpdate.h"
#include "Component/Update/TransformUpdate.h"
#include "Component/Update/CycleUpdate.h"
#include "Component/ComponentManager.h"
#include "Util/Util.h"
#include <iostream>
#include <boost/uuid/uuid_io.hpp>

void Main() {
  s3d::Console::Open();
  s3d::Window::Resize(800, 600);
  s3d::Optional<int&> opt;
  gsl::Entity entity_1 = gsl::Entity::CreateEntity(L"TestEntity_1");
  gsl::Entity entity_2(L"TestEntity_2"), entity_3 = gsl::Entity::FindEntityWithName(L"TestEntity_1");
  entity_1.CreateData(L"TestData_1", 10);
  s3d::FontAsset::Register(L"Font", 16, L"ÉÅÉCÉäÉI");
  s3d::Image image(L"data/Title.png");
  auto data_1 = entity_3.GetRawData<int>(L"TestData_1");
  gsl::Entity base
    = gsl::Entity::CreateEntity(L"BaseEntity")
    .InitTransform(gsl::TransformInitializer().Center({ 45,45 }).Rotation(Radians(30.0)))
    .CreateData(L"Absolute", 100);
  gsl::Entity circle
    = gsl::Entity::CreateEntity(L"CicleEntity")
    .InitTransform(gsl::TransformInitializer().Center({ 100,100 }).Scale({ 1.5,1.5 }).Rotation(Radians(45.0)))
    .SetParent(base)
    .CreateData(L"Circle", s3d::Circle({ 15,15 }, 5.0))
    .CreateData(L"Rect", s3d::Rect({ 30,30 }, { 30,15 }))
    .CreateData(L"Color", s3d::Palette::Gray)
    .CreateData(L"Position", s3d::Vec2::Zero)
    .CreateData(L"TmpPosition", s3d::Vec2::Zero)
    .AddComponent<gsl::Render::CircleRender>(L"CircleRender", 100, gsl::Render::ShapeRenderOption().Shape(L"Circle").Color(L"Color").Position(L"Position"))
    .AddComponent<gsl::Render::RectRender>(L"RectRender", 100, gsl::Render::ShapeRenderOption().Shape(s3d::Rect({ 30,30 }, { 30,15 })).Position(L"TmpPosition"))
    .AddComponent<gsl::Render::TextRender>(L"TextRender", 100, gsl::Render::TextRenderOption().Text(Util::SplitString(L"ÇƒÇ∑Ç∆\nÇﬂÇ¡ÇπÅ[Ç∂", L'\n')).FontAsset(s3d::FontAsset(L"Font")))
    .AddComponent<gsl::Render::DynamicTextureRender>(L"TextureRender", 90, gsl::Render::ImageRenderOption().Texture(s3d::DynamicTexture(image)))
    .AddComponent<gsl::Update::VariableUpdate<s3d::Vec2>>(L"PosAnimation", 100, gsl::Update::VariableUpdateOption().From(L"Position").To(s3d::Vec2(100, 100)).Target(L"Position").Time(1000ms).Easing(gsl::Easing::QuadInOut))
    .AddComponent<gsl::Update::TransformUpdate>(L"TransMoving", 100, gsl::Update::TransformOption().From(gsl::IDWaiting(L"CicleEntity")).To(gsl::Update::TransformData().Center({ 300,300 })).Time(1000ms).Easing(gsl::Easing::QuadInOut))
    .AddComponent<gsl::Update::CycleUpdate>(L"PosMoving", 100, gsl::Update::CycleOption().Time(500ms).Callback([](gsl::Update::UpdateComponent& com, const auto& t) {gsl::Entity(com.GetOwner()).GetData(L"TmpPosition").value() = s3d::Vec2(s3d::RandomPoint(50, 50)); }));
  auto* circle_entity = gsl::detail::EntityManager::FindEntityDetail(*circle.GetID());
  auto* circle_parent = gsl::detail::EntityManager::FindEntityDetail(*base.GetID());
  auto data_2 = entity_1.GetRawData<int>(L"TestData_1");
  while (System::Update()) {
    gsl::ComponentManager<gsl::Update::UpdateComponent>::Apply([](gsl::Update::UpdateComponent* com) {com->Update(); });
    gsl::ComponentManager<gsl::Render::RenderComponent>::Apply([](gsl::Render::RenderComponent* com) {com->Render(); });
  }
  s3d::Console::Close();
}