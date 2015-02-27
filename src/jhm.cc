#include "jhm.h"

using engine::component::BlockMovement;
using engine::component::Directional;
using engine::component::Drawable;
using engine::component::Entity;
using engine::component::Movable;
using engine::component::Player;

JHM::JHM() : running_(false) {

}

JHM::~JHM() {

}

void JHM::Run() {
  // Setup the game.
  Setup();

  // While the game is running...
  running_ = true;
  while (running_) {
    ProcessEvents();
    Loop();
    Render();
  }

  // Shutdown the game.
  Stop();
}

void JHM::Setup() {
  LOG->trace("JHM::Setup");

  // Create the main view.
  window_.create(sf::VideoMode(800, 600), "Harvest Moon");
  window_.clear();
  window_.setFramerateLimit(30);
  window_.setView(sf::View(sf::FloatRect(0, 0, 800, 600)));

  // When the window is closed, stop running.
  action_map_["quit"] = thor::Action(sf::Event::Closed);

  // Create the main character.
  LOG->info("Creating main character...");
  new Entity({
    (new Drawable("../assets/main-character.png", {7, 26}, {19, 29}))
      ->z_index(10000)
      ->location({200.0, 200.0})
      ->scale(2)
      ->hit_box({0, 28}),
    new Movable(4),
    new Player(action_map_, 4)
  });
  LOG->info("Done!");

  LOG->info("Creating background map...");
  new Entity({
    (new Drawable("../assets/main-farm-large.png"))->z_index(0),
  });
  LOG->info("Done!");

  LOG->info("Constructing boundaries...");

  // Vertical fences (0, 0, 7, 16).
  new Entity({
    (new Drawable("../assets/farm-fence-vertical.png", {0, 0}, {7, 16 * 26 - 6}))
      ->location({128.0, 110.0})->z_index(1002)->scale(2)->repeat(),
    new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-fence-vertical.png", {7, 0}, {-7, 16 * 35 + 10}))
      ->location({2004.0, 118.0})->z_index(1002)->scale(2)->repeat(),
    new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-fence-vertical.png", {0, 0}, {7, 16 * 4}))
      ->location({578.0, -16})->z_index(1002)->scale(2)->repeat(),
    new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-fence-vertical.png", {7, 0}, {-7, 16 * 4}))
      ->location({770.0, -16})->z_index(1002)->scale(2)->repeat(),
    new BlockMovement(),
  });

  // Horizontal fences (0, 0, 11, 16).
  new Entity({
    (new Drawable("../assets/farm-fence-horizontal.png", {7, 0}, {11 * 20, 16}))
      ->location({140.0, 102.0 - 22})->z_index(1002)->scale(2)->repeat(),
    new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-fence-horizontal.png", {7, 0}, {11 * 57, 16}))
      ->location({770.0, 102.0 - 22})->z_index(1002)->scale(2)->repeat(),
    new BlockMovement(),
  });

  // Vertial water edge. (0, 0, 8, 32).
  // Water corners. Inner corner (0, 0, 10, 10), Outer corner (10, 0, 10, 10).
  // Horizontal water edge. (0, 0, 32, 8)
  // TOP EDGE OF THE RIVER.
  new Entity({
    (new Drawable("../assets/farm-water-edge-corners.png", {10, 0}, {10, 10}))
      ->location({86.0, 706.0})->z_index(1001)->scale(2)->repeat(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-vertical.png", {0, 0}, {8, 35}))
      ->location({90.0, 716.0})->z_index(1000)->scale(2)->repeat(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-corners.png", {0, 0}, {10, 10}))
      ->location({93.0, 768.0})->z_index(1001)->scale(2)->repeat(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-corners.png", {10, 0}, {10, 10}))
      ->location({110.0, 768.0})->z_index(1001)->scale(2)->repeat(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-vertical.png", {0, 0}, {8, 155}))
      ->location({112.0, 785.0})->z_index(1000)->scale(2)->repeat(),
    new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-corners.png", {0, 0}, {10, 10}))
      ->location({118.0, 1086.0})->z_index(1001)->scale(2)->repeat(),
    new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-corners.png", {10, 0}, {10, 10}))
      ->location({133.0, 1086.0})->z_index(1001)->scale(2)->repeat(),
      new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-vertical.png", {0, 0}, {8, 25}))
      ->location({138.0, 1096.0})->z_index(1000)->scale(2)->repeat(),
    new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-corners.png", {0, 0}, {10, 10}))
      ->location({138.0, 1140.0})->z_index(1001)->scale(2)->repeat(),
      new BlockMovement(),
  });

  // TODO: need horizontal piece here.

  new Entity({
    (new Drawable("../assets/farm-water-edge-corners.png", {10, 0}, {10, 10}))
      ->location({158.0, 1140.0})->z_index(1001)->scale(2)->repeat(),
      new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-vertical.png", {0, 0}, {8, 40}))
      ->location({162.0, 1150.0})->z_index(1000)->scale(2)->repeat(),
    new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-corners.png", {0, 0}, {10, 10}))
      ->location({166.0, 1222.0})->z_index(1001)->scale(2)->repeat(),
      new BlockMovement(),
  });

  // TODO: need horizontal piece here.

  new Entity({
    (new Drawable("../assets/farm-water-edge-corners.png", {10, 0}, {10, 10}))
      ->location({230.0, 1222.0})->z_index(1001)->scale(2)->repeat(),
      new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-vertical.png", {0, 0}, {8, 20}))
      ->location({236.0, 1232.0})->z_index(1000)->scale(2)->repeat(),
    new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-corners.png", {0, 0}, {10, 10}))
      ->location({230.0, 1250.0})->z_index(1001)->scale(2)->repeat(),
      new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-horizontal.png", {0, 0}, {125, 8}))
      ->location({240.0, 1250.0})->z_index(1000)->scale(2)->repeat(),
      new BlockMovement(),
  });

  new Entity({
    (new Drawable("../assets/farm-water-edge-horizontal.png", {0, 0}, {739, 8}))
      ->location({572.0, 1250.0})->z_index(1000)->scale(2)->repeat(),
      new BlockMovement(),
  });

  LOG->info("Done!");

  LOG->trace("done JHM::Setup");
}

void JHM::ProcessEvents() {
  action_map_.update(window_);
}

void JHM::Loop() {
  LOG->trace("JHM::Loop");

  for (Entity* entity : Entity::GetAllEntities()) {
    entity->Update(action_map_);
  }

  // If we have to quit, then do so.
  if (action_map_.isActive("quit")) {
    running_ = false;
  }

  LOG->trace("Done JHM::Loop");
}

void JHM::Render() {
  LOG->trace("JHM::Render");

  window_.clear();

  // Update the view to match the player.
  for (const Entity* entity : Entity::GetEntitiesWithComponent<Player>()) {
    sf::View view = window_.getView();
    view.setCenter(entity->GetComponent<Drawable>().Sprite().getPosition());
    window_.setView(view);
  }

  // Render all rendable objects.
  std::vector<Entity*> entities = Entity::GetEntitiesWithComponent<Drawable>();
  std::sort(entities.begin(), entities.end(), [](Entity* a, Entity* b) {
    return a->GetComponent<Drawable>().z_index() <
           b->GetComponent<Drawable>().z_index();
  });

  for (const Entity* entity : entities) {
    entity->GetComponent<Drawable>().Draw(window_);
  }

  // Display the window.
  window_.display();

  LOG->trace("Done JHM::Render");
}

void JHM::Stop() {
  window_.close();
}
