/* in the name of Allah */

#ifndef I8D016DC6_85B7_452C_9BFA_000B31405394
#define I8D016DC6_85B7_452C_9BFA_000B31405394

#include <thread>
#include <boost/asio.hpp>
#include <boost/signals2.hpp>

//template <typename... Args>
//class event {
//	boost::signals2::signal<void(Args...)> sig_;
//
//public:
//	event() {}
//	virtual ~event() = default;
//
//	template <typename F>
//	auto connect(F &&f) -> void {
//		sig_.connect(std::move(f));
//	}
//
//	auto operator()(Args &&...args) -> void { sig_(args...); }
//};

template <typename... Args>
using event = boost::signals2::signal<void(Args...)>;

class handler {
	std::unique_ptr<boost::asio::io_context> io_;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_;

public:
	handler()
		: io_ { new boost::asio::io_context {} }
		, work_ { boost::asio::make_work_guard(*io_) } {
		(std::thread { [this] { io_->run(); } }).detach();
	}

	template <typename... Args, typename F>
	auto handle(event<Args...> &e, F &&f) -> void {
		e.connect([this, f = std::forward<F>(f)](Args... args) { io_->post(std::bind(f, args...)); });
	}

	virtual ~handler() = default;
};

class framework {
public:
	framework() {}
	virtual ~framework() = default;
};

#endif /* !I8D016DC6_85B7_452C_9BFA_000B31405394 */
