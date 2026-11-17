// C wrappers around clasp's ClaspFacade, built only for static linking.
//
// The facade pointer is obtained with clingo_control_clasp_facade(). Like the
// C API, each function returns whether the call was successful and sets a
// clingo error otherwise.

#include <clasp/clasp_facade.h>
#include <clingo.h>

#include <cstdint>
#include <exception>

namespace {

Clasp::ClaspFacade const &facade(void const *clasp) { return *static_cast<Clasp::ClaspFacade const *>(clasp); }

template <class F> bool wrap(F f) {
    try {
        f();
        return true;
    } catch (std::exception const &e) {
        clingo_set_error(clingo_error_runtime, e.what());
    } catch (...) {
        clingo_set_error(clingo_error_unknown, "unknown error");
    }
    return false;
}

} // namespace

extern "C" {

bool clingo_sys_clasp_facade_step(void const *clasp, int *step) {
    return wrap([&] { *step = facade(clasp).step(); });
}

bool clingo_sys_clasp_facade_solving(void const *clasp, bool *solving) {
    return wrap([&] { *solving = facade(clasp).solving(); });
}

bool clingo_sys_clasp_facade_interrupted(void const *clasp, bool *interrupted) {
    return wrap([&] { *interrupted = facade(clasp).interrupted(); });
}

bool clingo_sys_clasp_facade_num_vars(void const *clasp, uint32_t *num) {
    return wrap([&] { *num = facade(clasp).ctx.numVars(); });
}

bool clingo_sys_clasp_facade_num_eliminated_vars(void const *clasp, uint32_t *num) {
    return wrap([&] { *num = facade(clasp).ctx.numEliminatedVars(); });
}

bool clingo_sys_clasp_facade_num_constraints(void const *clasp, uint32_t *num) {
    return wrap([&] { *num = facade(clasp).ctx.numConstraints(); });
}

bool clingo_sys_clasp_facade_concurrency(void const *clasp, uint32_t *num) {
    return wrap([&] { *num = facade(clasp).ctx.concurrency(); });
}

} // extern "C"
