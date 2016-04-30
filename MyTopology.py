from mininet.topo import Topo
from mininet.net import Mininet
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel

class SingleSwitchTopo(Topo):
    "Single switch connected to n hosts"
    def__init__(self, n=2, **opts):

# initiate topology and default options
Topo.__init__(self, **opts)
switch = self.addSwitch('s1')

# Python's range (N) generates 0....N-1 for h in range (n):
host = self.addHost('h%s' % (h+1))
self.addLink(host,switch)

def simpleTest():
    "Create and Test a simple network"
    topo = SingleSwitchTopo(n=4)
    net = Mininet(topo)
    net.start()
    print "Dumping host connections"
    dumpNodeConnections(net.hosts)
    print "Testing network connectivity"
    net.pingAll()
    net.stop()

    if__name__=='__main__':
#Tell mininet to print useful information
setLogLevel('info')
simpleTest()
