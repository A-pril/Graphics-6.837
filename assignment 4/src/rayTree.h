#ifndef _RAY_TREE_H
#define _RAY_TREE_H

#include "ray.h"
#include <GL/freeglut.h>

// ====================================================================
// ====================================================================
// data structure to store a segment

class Segment {

public:

  // CONSTRUCTOR & DESTRUCTOR
  Segment() { Clear(); }
  Segment(const Ray &ray, float tstart, float tstop) {
    // first clamp the segment to "reasonable" values 
    // to make sure it is drawn correctly in OpenGL
    if (tstart < -100) tstart = -100;
    if (tstop  >  100) tstop  =  100;
    a = ray.pointAtParameter(tstart);
    b = ray.pointAtParameter(tstop); }
  Segment(const Segment &s) { a = s.a; b = s.b; }
  ~Segment() {}
  
  void Clear() { a = Vec3f(0,0,0); b = Vec3f(0,0,0); }
  void Print(const char *s) {
    printf (" %s (%6.3f %6.3f %6.3f) -> (%6.3f %6.3f %6.3f)\n",
	    s, a.x(),a.y(),a.z(), b.x(),b.y(),b.z());
  }
  void paint() {
    glVertex3f(a.x(),a.y(),a.z());
    glVertex3f(b.x(),b.y(),b.z());
  }
  
private:
  // REPRESENTATION
  Vec3f a;
  Vec3f b;
};

// ====================================================================
// data structure to hold a variable number of segments

class SegmentVector {

public:

  // CONSTRUCTOR & DESTRUCTOR
  SegmentVector() {
    num_segments = 0;
    size = 10;
    segments = new Segment[size]; }
  ~SegmentVector() { delete [] segments; }
  void Clear() { num_segments = 0; }

  // ACCESSORS
  int getNumSegments() { return num_segments; }
  Segment getSegment(int i) { 
    assert (i >= 0 && i < num_segments);
    return segments[i]; }

  // MODIFIERS
  void addSegment(const Segment &s) {
    if (size == num_segments) {
      // double the size of the array and copy the pointers
      int new_size = size * 2;
      Segment *new_segments = new Segment[new_size];
      int i;
      for (i = 0; i < size; i++) {
	new_segments[i] = segments[i];
      }
      delete [] segments;
      segments = new_segments;
      size = new_size;
    }
    segments[num_segments] = s;
    num_segments++;
  }

private:

  // REPRESENTATION
  Segment *segments;
  int size;
  int num_segments;
};

// ====================================================================
// ====================================================================
//
// This class only contains static variables and static member
// functions so there is no need to call the constructor, destructor
// etc.  It's just a wrapper for the ray tree visualization data.
//

class RayTree {

public:

  // most of the time the RayTree is NOT activated, so the segments
  // are NOT updated
  static void Activate() { Clear(); activated = 1; }
  static void Deactivate() { activated = 0; }

  // when activated, these function calls store the segments of the tree
  static void SetMainSegment(const Ray &ray, float tstart, float tstop) {
    if (!activated) return;
    main_segment = Segment(ray,tstart,tstop);
  }
  static void AddShadowSegment(const Ray &ray, float tstart, float tstop) {
    if (!activated) return;
    shadow_segments.addSegment(Segment(ray,tstart,tstop));
  }
  static void AddReflectedSegment(const Ray &ray, float tstart, float tstop) {
    if (!activated) return;
    reflected_segments.addSegment(Segment(ray,tstart,tstop));
  }
  static void AddTransmittedSegment(const Ray &ray, float tstart, float tstop) {
    if (!activated) return;
    transmitted_segments.addSegment(Segment(ray,tstart,tstop));
  }

  static void paint();
  static void Print();

private:
  
  // HELPER FUNCTIONS
  static void paintHelper(const Vec4f &m,const Vec4f &s,const Vec4f &r,const Vec4f &t);
  static void Clear() {
    main_segment.Clear();
    shadow_segments.Clear();
    reflected_segments.Clear();
    transmitted_segments.Clear();
  }

  // REPRESENTATION
  static int activated;
  static Segment main_segment;
  static SegmentVector shadow_segments;
  static SegmentVector reflected_segments;
  static SegmentVector transmitted_segments;
};

// ====================================================================
// ====================================================================

#endif
