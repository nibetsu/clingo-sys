#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]

include!("bindings.rs");

// C wrappers around clasp's ClaspFacade (see clasp_shim.cpp), only available with static linking
#[cfg(feature = "static-linking")]
extern "C" {
    pub fn clingo_sys_clasp_facade_step(
        clasp: *const ::std::os::raw::c_void,
        step: *mut ::std::os::raw::c_int,
    ) -> bool;
    pub fn clingo_sys_clasp_facade_solving(
        clasp: *const ::std::os::raw::c_void,
        solving: *mut bool,
    ) -> bool;
    pub fn clingo_sys_clasp_facade_interrupted(
        clasp: *const ::std::os::raw::c_void,
        interrupted: *mut bool,
    ) -> bool;
    pub fn clingo_sys_clasp_facade_num_vars(
        clasp: *const ::std::os::raw::c_void,
        num: *mut u32,
    ) -> bool;
    pub fn clingo_sys_clasp_facade_num_eliminated_vars(
        clasp: *const ::std::os::raw::c_void,
        num: *mut u32,
    ) -> bool;
    pub fn clingo_sys_clasp_facade_num_constraints(
        clasp: *const ::std::os::raw::c_void,
        num: *mut u32,
    ) -> bool;
    pub fn clingo_sys_clasp_facade_concurrency(
        clasp: *const ::std::os::raw::c_void,
        num: *mut u32,
    ) -> bool;
}
