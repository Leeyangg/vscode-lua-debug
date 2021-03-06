#include <debugger/io/client.h>

namespace vscode { namespace io {
    client::client(const bee::net::endpoint& ep)
		: session(new bee::net::poller_t)
        , connecter(get_poller())
	{
        bee::net::socket::initialize();
        connecter.connect(ep, std::bind(&client::event_connect, this, std::placeholders::_1));
	}

    client::~client() {
	}

	void client::update(int ms)
	{
		get_poller()->wait(ms);
	}

    void client::event_connect(bee::net::socket::fd_t fd)
    {
        attach(fd);
    }

    void client::close()
    {
        session::close();
        while (!session::is_closed()) {
            get_poller()->wait(0);
            session::update(0);
        }
    }
}}
