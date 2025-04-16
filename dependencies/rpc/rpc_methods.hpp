#include "rpc.hpp"

#ifndef RPC_SERVER
/// The different kinds of alignments a layout can perform.
enum class Alignment : uint8_t {
    Minimum = 0, ///< Take only as much space as is required.
    Middle,      ///< Center align.
    Maximum,     ///< Take as much space as is allowed.
    Fill         ///< Fill according to preferred sizes.
};

/// The direction of data flow for a layout.
enum class Orientation {
    Horizontal = 0, ///< Layout expands on horizontal axis.
    Vertical        ///< Layout expands on vertical axis.
};
#endif

RPC_ENUM(Alignment, uint8_t)
RPC_ENUM(Orientation, uint8_t)

// MARK: Layout
BEGIN_CLASS(Layout)
END_CLASS()

// MARK: BoxLayout
BEGIN_CLASS(BoxLayout)
CONSTRUCTOR3(BoxLayout, Orientation, Alignment, int)
CONSTRUCTOR4(BoxLayout, Orientation, Alignment, int, int)
END_CLASS()

// MARK: BoxLayout
BEGIN_CLASS(GridLayout)
CONSTRUCTOR5(GridLayout, Orientation, int, Alignment, int, int)
END_CLASS()

// MARK: Widget
BEGIN_CLASS(Widget)
CONSTRUCTOR1(Widget, Widget*)

CONST_METHOD0(const Widget*, parent)

METHOD0(Layout*, layout)
CONST_METHOD0(const Layout*, layout)
METHOD1(void, set_layout, Layout*)

CONST_METHOD0(bool, visible)
METHOD1(void, set_visible, bool)
CONST_METHOD0(int, fixed_width)
CONST_METHOD0(int, fixed_height)
METHOD1(void, set_fixed_width, int)
METHOD1(void, set_fixed_height, int)

CONST_METHOD0(bool, enabled)
METHOD1(void, set_enabled, bool)

CONST_METHOD0(bool, focused)
METHOD1(void, set_focused, bool)
METHOD0(void, request_focus)

CONST_METHOD0(const std::string&, tooltip)
METHOD1(void, set_tooltip, const std::string&)

CONST_METHOD0(int, font_size)
METHOD1(void, set_font_size, int)
CONST_METHOD0(bool, has_font_size)

END_CLASS()

// MARK: Label
BEGIN_SUBCLASS(Label, Widget)
CONSTRUCTOR2(Label, Widget*, const std::string&)
CONSTRUCTOR3(Label, Widget*, const std::string&, const std::string&)
CONSTRUCTOR4(Label, Widget*, const std::string&, const std::string&, int)
END_CLASS()

// MARK: Button
BEGIN_SUBCLASS(Button, Widget)
CONSTRUCTOR3(Button, Widget*, const std::string &, int)
CONST_METHOD0(const std::string&, caption)
METHOD1(void, set_caption, const std::string&)
METHOD1(void, set_callback, const std::function<void()> &)
END_CLASS()

// MARK: RPCContext
BEGIN_CLASS(RPCContext)
CONSTRUCTOR0(RPCContext)
CONST_METHOD1(Widget*, sidebar, const std::string&)
CONST_METHOD0(void, performLayout)
END_CLASS()
