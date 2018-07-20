import time
import os

import subprocess

#t1c = time.clock()
t1 = time.time()
subprocess.call([r"/afs/nd.edu/coursesp.18/cse/cse30341.01/dropbox/teams2/team_oops/project4/threadedRE", "-level", "1", "Dataset-Medium.pcap", "Dataset-Big.pcap", "Dataset-Medium.pcap"])
t2 = time.time()

print(float(t2-t1))

#os.startfile("/afs/nd.edu/coursesp.18/cse/cse30341.01/dropbox/teams2/JAME/project4/ThreadedRE")

