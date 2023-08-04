#include "Neutrino.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include "supera/base/meatloaf.h"

namespace supera {


  std::string Neutrino::dump() const
  {
    std::stringstream ss;
    std::stringstream buf;
    ss  << "      \033[95m" << "Neutrino " << " (VtxId, PdgCode) = (" << StringifyInstanceID(vertex_id) << ", " << pdg << ")\033[00m " << std::endl

    buf << "      ";

    ss << buf.str() << "Vertex   (x, y, z, t) = (" << vtx.pos.x << "," << vtx.pos.y << "," << vtx.pos.z << "," << vtx.time << ")" << std::endl
       << buf.str() << "Momentum (px, py, pz) = (" << px << "," << py << "," << pz << ")" << std::endl
    ss << std::endl;

    return ss.str();

  }
}
