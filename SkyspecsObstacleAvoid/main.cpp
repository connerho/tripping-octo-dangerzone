// API
// Event - driven
// IPC
// produce and consume events
// Obsever - GPS, IMU, etc. -> position estimate

// Agent - business logic, business logic
// look for something that is going wrong about the doesnt hitting something
// obstacles neearby
// produce a plan about how to get the drone away from the thing
// Avoidance Planner

enum FLY_DIRECTION
{
  HALT,
};

enum Event;

class AvoidancePlanner
{
  public:
  AvoidancePlanner();
  ~AvoidancePlanner();

  void HandleEvent(const double* velocity, const double* acceleration, const double* position, const map* data, double output[3]);

  private:
  double position[3];
  double task_rate;
};
