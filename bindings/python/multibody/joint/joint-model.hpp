//
// Copyright (c) 2015-2022 CNRS INRIA
//

#ifndef __pinocchio_python_multibody_joint_joint_model_hpp__
#define __pinocchio_python_multibody_joint_joint_model_hpp__

#include <boost/python.hpp>

#include "pinocchio/multibody/joint/joint-generic.hpp"
#include "pinocchio/bindings/python/multibody/joint/joint-derived.hpp"
#include "pinocchio/bindings/python/utils/printable.hpp"

namespace pinocchio
{
  namespace python
  {
    namespace bp = boost::python;
  
    template<typename JointModel>
    struct ExtractJointVariantTypeVisitor
    {
      typedef typename JointModel::JointCollection JointCollection;
      typedef bp::object result_type;

      template<typename JointModelDerived>
      result_type operator()(const JointModelBase<JointModelDerived> & jmodel) const
      {
        bp::object obj(boost::ref(jmodel.derived()));
        return obj;
      }
      
      static result_type extract(const JointModel & joint_generic)
      {
        return boost::apply_visitor(ExtractJointVariantTypeVisitor(), joint_generic);
      }
    };
  
    template<typename JointModel>
    struct JointModelPythonVisitor
    {
      
      static void expose()
      {
        bp::class_<JointModel>("JointModel",
                               "Generic Joint Model",
                               bp::no_init)
        .def(bp::init<JointModel>(bp::arg("self"),"Default constructor"))
        .def(bp::init<JointModel>(bp::args("self","other"),"Copy constructor"))
        .def(JointModelBasePythonVisitor<JointModel>())
        .def(PrintableVisitor<JointModel>())
        .def("extract",ExtractJointVariantTypeVisitor<JointModel>::extract,
             bp::arg("self"),
             "Returns a reference of the internal joint managed by the JointModel",
             bp::with_custodian_and_ward_postcall<0,1>())
        ;
      }

    }; 
    
}} // namespace pinocchio::python

#endif // ifndef __pinocchio_python_multibody_joint_joint_model_hpp__
