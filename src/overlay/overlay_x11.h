#include <memory>
namespace p0
{
class overlay_x11 final
{
public:
    struct sdl_details;

    explicit overlay_x11() noexcept;
    ~overlay_x11() noexcept;

    overlay_x11(const overlay_x11&)           = delete;
    overlay_x11(overlay_x11&&)                = delete;
    overlay_x11 operator=(const overlay_x11&) = delete;
    overlay_x11 operator=(overlay_x11&&)      = delete;

    void iterate();

    std::unique_ptr<sdl_details> details;

private:
};
}; // namespace p0