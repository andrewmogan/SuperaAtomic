/**
 * \file Neutrino.h
 *
 * \ingroup base
 *
 * \brief Class def header for a class supera::Neutrino
 *
 * @author kazuhiro
 */

/** \addtogroup base
    @{*/
#ifndef __NEUTRINO_H__
#define __NEUTRINO_H__

#include <array>
#include <iostream>
#include <vector>

#include "supera/base/Point.h"
#include "supera/base/SuperaType.h"
#include "supera/base/Voxel.h"
namespace supera {

  /**
     \class Neutrino
     \brief Neutrino/Interaction-wise truth information data from GENIE
  */
  class Neutrino{

  public:

    /// Default constructor
      /* Attribute to create
        ('event_id','vertex_id','vertex',
         'target','reaction','isCC','isQES','isMEC','isRES','isDIS','isCOH',
         'Enu','nu_4mom','nu_pdg','Elep','lep_mom','lep_ang','lep_pdg',
         'q0','q3','Q2',
         'x','y'
      */
    Neutrino()
      : id        (kINVALID_INDEX)
      , vertex_id (kINVALID_INDEX)
      , pdg       (kINVALID_PDG)
      , px        (kINVALID_DOUBLE)
      , py        (kINVALID_DOUBLE)
      , pz        (kINVALID_DOUBLE)
      //, _nu_trackid       (kINVALID_UINT)
    {}

    /// Default destructor
    ~Neutrino(){}

    // Dump method
    std::string dump() const;

    /// neutrino's ID getter
    InstanceID_t id;            ///< "ID" of this particle in ParticleSet collection
    InstanceID_t vtx_id;            ///< "ID" of this particle in ParticleSet collection
    Vertex         vtx;         ///< (x,y,z,t) of particle's vertex information
    PdgCode_t      pdg;         ///< PDG code
    double         px,py,pz;    ///< (x,y,z) component of particle's initial momentum
  };

  /**
     \class NeutrinoSet
     \brief Neutrino/Interaction collection
  */
  class NeutrinoSet {
  public:
	NeutrinoSet() {}
    virtual ~NeutrinoSet() {}

    void clear() { _neutrino_v.clear(); }

    inline const std::vector<larcv::Neutrino>& as_vector() const
    { return _neutrino_v; }

    void set(const std::vector<larcv::Neutrino>& neutrino_v);

    void append(const larcv::Neutrino& neutrino);

    void emplace_back(larcv::Neutrino&& neutrino);

    void emplace(std::vector<larcv::Neutrino>&& neutrino_v);


  private:

    std::vector<larcv::Neutrino> _neutrino_v; ///< a collection of neutrinos (index maintained)
  };
}
#endif
/** @} */ // end of doxygen group
