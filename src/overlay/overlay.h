
class overlay final
{
public:
    explicit overlay() noexcept;
    ~overlay() noexcept;

    overlay(const overlay&)           = delete;
    overlay(overlay&&)                = delete;
    overlay operator=(const overlay&) = delete;
    overlay operator=(overlay&&)      = delete;

private:
    void* root_window = nullptr;
};