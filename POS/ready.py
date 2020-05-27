Ntot = 1000000.
import subprocess
result = subprocess.run(['tail', '-1', 'out.data'], stdout=subprocess.PIPE)
print( str( 100.*(1.+float(result.stdout.decode('utf-8').split(" ")[0]))/Ntot)+" % done" )
