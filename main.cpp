/* in the name of Allah */

#include "framework.hpp"

#include <thread>
#include <mutex>
#include <iostream>
#include <memory>
#include <boost/asio.hpp>

class steady_timer {
	std::unique_ptr<boost::asio::io_context> io_ { new boost::asio::io_context {} };
	std::unique_ptr<boost::asio::steady_timer> timer_;

public:
	steady_timer(int ms_wait, std::function<void(boost::system::error_code const &)> &&cb) {
		timer_ = std::make_unique<boost::asio::steady_timer>(*io_);
		timer_->expires_from_now(std::chrono::milliseconds { ms_wait });
		timer_->async_wait(std::move(cb));
	}
	auto start() -> void { io_->run(); }
};

std::mutex m;

auto log(std::string s, std::thread::id const &id) -> void {
	std::unique_lock<std::mutex> lock { m };
	std::cout << s << ": " << id << std::endl;
}

auto main(int argc, char const **argv) -> int {
	//steady_timer timer { 3000, [](auto error) { std::cout << "called after 3 seconds" << std::endl; } };

	// timer.start();

	event<std::string> e;
	handler h {};

	for (int i = 0; i < 5; i++) {
		(new handler {})->handle(e, [](auto name) {
			log(name, std::this_thread::get_id());
		});
	}

	//h.connect(e, [](auto name) { std::cout << name << std::this_thread::get_id() << std::endl; });

	// e.connect([](auto name) { std::cout << name << std::endl; });

	e("test");

	std::cin.get();

	return 0;
}
