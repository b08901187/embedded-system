from bluepy.btle import Peripheral, UUID
from bluepy.btle import Scanner, DefaultDelegate

class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)
    def handleDiscovery(self, dev, isNewDev, isNewData):
        if isNewDev:
            print "Discovered device", dev.addr
        elif isNewData:
            print "Received new data from", dev.addr
            
class localDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)
    def handleNotification(self, cHandle, localdata):
        print ("Notification is 0x"+format(cHandle, '02x'))
        print (localdata)
        

scanner = Scanner().withDelegate(ScanDelegate())
devices = scanner.scan(3.0)
n=0
for dev in devices:
    print ("%d: Device %s (%s), RSSI=%d dB" % (n, dev.addr,
dev.addrType, dev.rssi))
    n += 1
    for (adtype, desc, value) in dev.getScanData():
        print (" %s = %s" % (desc, value))
number = input('Enter your device number: ')
print 'Device', number
print(devices[number].addr)


print ("Connecting...")
dev = Peripheral(devices[number].addr, 'random')
dev.setDelegate(localDelegate())

print ("Services...")
for svc in dev.services:
    print (str(svc))
try:
    testService = dev.getServiceByUUID(UUID(0xfff0))
    '''
    for ch in testService.getCharacteristics():
        print (str(ch))
    for ch in dev.getCharacteristics():
        if (ch.supportsRead()):
            print (ch.read())
        else:
            print('..'+str(ch))
    '''
    for descriptor in dev.getDescriptors():
        print(descriptor)
        for uuid in range(0x2901, 0x2905):           
            if descriptor.uuid == uuid:
                print 'handle:',descriptor.handle        
        dev.writeCharacteristic(descriptor.handle, b'Who is Cody?')        
        print '\n'
    
    while True:
        if dev.waitForNotifications(1.0):
            print("Notify")
            continue
           
finally:
    dev.disconnect() 