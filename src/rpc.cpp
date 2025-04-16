#define RPC_SERVER

#include <tev/ImageViewer.h>

#include <nanogui/widget.h>
#include <nanogui/button.h>
#include <nanogui/layout.h>
#include <nanogui/label.h>

namespace tev {
extern ImageViewer* sImageViewer;
}

using namespace nanogui;

class RPCContext {
public:
    RPCContext() {
        printf("[rpctx] context created\n");
    }

    Widget* sidebar(const std::string &imageName) const {
        printf("[rpctx] asked to create sidebar\n");
        return tev::sImageViewer->getSidebar(imageName);
    }

    void performLayout() const {
        // Directly layouting from the IPC thread can cause segfaults.
        // Ask main thread to do layouting when it is ready to do so.
        tev::sImageViewer->requestLayoutUpdate();
    }
};

#include <rpc_methods.hpp>
