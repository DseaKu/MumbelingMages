#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#define MAX_PERFORMANCE_TRACKERS 100

typedef struct {
  char *name;
  double start_time;
  double end_time;
  double elapsed_time;
  double total_elapsed_time;
  int runs;
} PerformanceTracker;

void StartPerformanceTracker(const char *name);
void EndPerformanceTracker(const char *name);
void PrintPerformanceTrackers(void);
void WritePerformanceTrackersToFile(const char *filename);
void CleanupPerformanceTrackers(void);

#endif // PERFORMANCE_H
