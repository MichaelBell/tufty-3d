import sys
import math

name = sys.argv[1]
print(name)

file = open("{}.obj".format(name), "r")

vertices = []
faces = []

for line in file:
  if line.startswith("v"):
    v = [float(v) for v in line.split()[1:4]]
    vertices.append((-v[2], v[1], v[0]))
  elif line.startswith("f"):
    faces.append([int(f)-1 for f in line.split()[1:4]])
  
file.close()

def compute_normal(v0, v1, v2):
  a = [(v1[i] - v0[i]) for i in range(3)]
  b = [(v2[i] - v0[i]) for i in range(3)]
  
  v = [a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]]
  l = math.sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])
  v = [x/l for x in v]
  return v

sys.stdout = open("{}.cpp".format(name), "w")

fmt = { "name": name }

print("""#include "common.h"
#include "model.h"
#include "lighting.h"

namespace {
""")
print("constexpr __in_flash(\"model\") Vec3D {name}_vertices[] = {{".format(**fmt))
for v in vertices:
  print("  { %ff, %ff, %ff }," % (v[0], v[1], v[2]))
print("};")
print()
print("Triangle {name}_tris[] = {{".format(**fmt))
for f in faces:
  n = compute_normal(vertices[f[0]], vertices[f[1]], vertices[f[2]])
  print("  { %d, %d, %d, 0, { %ff, %ff, %ff } }," % (f[0], f[1], f[2], n[0], n[1], n[2]))  
print("};")
print("""
Material {name}_mats[1];

Model {name}_model {{
  {name}_vertices,
  {name}_tris,
  {name}_mats,
  sizeof({name}_vertices) / sizeof({name}_vertices[0]),
  sizeof({name}_tris) / sizeof({name}_tris[0]),
  sizeof({name}_mats) / sizeof({name}_mats[0])
}};

bool {name}_model_inited = false;
}}

Model& get_{name}_model() {{
  if (!{name}_model_inited) {{
    {name}_mats[0] = make_material_for_colour(pimoroni::RGB(255, 255, 0));
    
    {name}_model_inited = true;
  }}
  
  return {name}_model;
}}
""".format(**fmt))