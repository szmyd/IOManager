#pragma once
#include "io_thread.hpp"
#include "io_interface.hpp"

struct spdk_thread;
namespace iomgr {
class IOReactorSPDK : public IOReactor {
    friend class IOManager;

public:
    IOReactorSPDK() = default;
    int add_iodev_to_reactor(const io_device_ptr& iodev) override;
    int remove_iodev_from_reactor(const io_device_ptr& iodev) override;
    bool send_msg(const iomgr_msg& msg) override;

    bool is_iodev_addable(const io_device_ptr& iodev) const override;
    io_thread_id_t my_io_thread_id() const override { return io_thread_id_t(m_sthread); };

    static void deliver_to_thread(spdk_thread*, const iomgr_msg&);

private:
    bool iocontext_init() override;
    void iocontext_exit() override;
    void listen() override;

private:
    spdk_thread* m_sthread = nullptr;
};
} // namespace iomgr
