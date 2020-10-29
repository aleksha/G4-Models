
from math import atan, pi
from ostap.histos.graphs import *

import ROOT, random
import ostap.io.root_file

from array import array

v_Tp     = array ( 'd', [ 0 ] )
v_Ee     = array ( 'd', [ 0 ] )
v_THETAp = array ( 'd', [ 0 ] )
v_THETAe = array ( 'd', [ 0 ] )
v_PHIp   = array ( 'd', [ 0 ] )
v_PHIe   = array ( 'd', [ 0 ] )
v_xpos   = array ( 'd', [ 0 ] )
v_ypos   = array ( 'd', [ 0 ] )
v_zpos   = array ( 'd', [ 0 ] )

v_peak0 = array ( 'd', [ 0 ] )
v_peak1 = array ( 'd', [ 0 ] )
v_peak2 = array ( 'd', [ 0 ] )
v_peak3 = array ( 'd', [ 0 ] )
v_peak4 = array ( 'd', [ 0 ] )
v_peak5 = array ( 'd', [ 0 ] )
v_peak6 = array ( 'd', [ 0 ] )
v_peak7 = array ( 'd', [ 0 ] )
v_peak8 = array ( 'd', [ 0 ] )

v_energy0 = array ( 'd', [ 0 ] )
v_energy1 = array ( 'd', [ 0 ] )
v_energy2 = array ( 'd', [ 0 ] )
v_energy3 = array ( 'd', [ 0 ] )
v_energy4 = array ( 'd', [ 0 ] )
v_energy5 = array ( 'd', [ 0 ] )
v_energy6 = array ( 'd', [ 0 ] )
v_energy7 = array ( 'd', [ 0 ] )
v_energy8 = array ( 'd', [ 0 ] )
v_T       = array ( 'd', [ 0 ] )

v_start0 = array ( 'd', [ 0 ] )
v_start1 = array ( 'd', [ 0 ] )
v_start2 = array ( 'd', [ 0 ] )
v_start3 = array ( 'd', [ 0 ] )
v_start4 = array ( 'd', [ 0 ] )
v_start5 = array ( 'd', [ 0 ] )
v_start6 = array ( 'd', [ 0 ] )
v_start7 = array ( 'd', [ 0 ] )
v_start8 = array ( 'd', [ 0 ] )

v_end0 = array ( 'd', [ 0 ] )
v_end1 = array ( 'd', [ 0 ] )
v_end2 = array ( 'd', [ 0 ] )
v_end3 = array ( 'd', [ 0 ] )
v_end4 = array ( 'd', [ 0 ] )
v_end5 = array ( 'd', [ 0 ] )
v_end6 = array ( 'd', [ 0 ] )
v_end7 = array ( 'd', [ 0 ] )
v_end8 = array ( 'd', [ 0 ] )

v_xCSC = array ( 'd', [ 0 ] )
v_yCSC = array ( 'd', [ 0 ] )
v_zCSC = array ( 'd', [ 0 ] )


from ostap.core.core import ROOTCWD

gen_file = ROOT.TFile("gen.root","READ")
out_file = ROOT.TFile("out.root","READ")
csc_file = ROOT.TFile("csc.root","READ")

gen_tree = gen_file.get("gen")
out_tree = out_file.get("out")
csc_tree = csc_file.get("out")


with ROOTCWD() , ROOT.TFile.Open( "new.root" , "RECREATE" ) as root_file:
    root_file.cd ()
    tree = ROOT.TTree ( 'tree','tree' )
    tree.SetDirectory ( root_file  )

    tree.Branch ( 'THETAp' , v_THETAp , 'THETAp/D')
    tree.Branch ( 'THETAe' , v_THETAe , 'THETAe/D')
    tree.Branch ( 'PHIp'   , v_PHIp   , 'PHIp/D'  )
    tree.Branch ( 'PHIe'   , v_PHIe   , 'PHIe/D'  )
    tree.Branch ( 'Tp'     , v_Tp     , 'Tp/D'    )
    tree.Branch ( 'Ed'     , v_Ee     , 'Ee/D'    )
    tree.Branch ( 'xpos'   , v_xpos   , 'xpos/D'  )
    tree.Branch ( 'ypos'   , v_ypos   , 'ypos/D'  )
    tree.Branch ( 'zpos'   , v_zpos   , 'zpos/D'  )

    tree.Branch ( 'peak0' , v_peak0 , 'peak0/D' )
    tree.Branch ( 'peak1' , v_peak1 , 'peak1/D' )
    tree.Branch ( 'peak2' , v_peak2 , 'peak2/D' )
    tree.Branch ( 'peak3' , v_peak3 , 'peak3/D' )
    tree.Branch ( 'peak4' , v_peak4 , 'peak4/D' )
    tree.Branch ( 'peak5' , v_peak5 , 'peak5/D' )
    tree.Branch ( 'peak6' , v_peak6 , 'peak6/D' )
    tree.Branch ( 'peak7' , v_peak7 , 'peak7/D' )
    tree.Branch ( 'peak8' , v_peak8 , 'peak8/D' )

    tree.Branch ( 'energy0' , v_energy0 , 'energy0/D' )
    tree.Branch ( 'energy1' , v_energy1 , 'energy1/D' )
    tree.Branch ( 'energy2' , v_energy2 , 'energy2/D' )
    tree.Branch ( 'energy3' , v_energy3 , 'energy3/D' )
    tree.Branch ( 'energy4' , v_energy4 , 'energy4/D' )
    tree.Branch ( 'energy5' , v_energy5 , 'energy5/D' )
    tree.Branch ( 'energy6' , v_energy6 , 'energy6/D' )
    tree.Branch ( 'energy7' , v_energy7 , 'energy7/D' )
    tree.Branch ( 'energy8' , v_energy8 , 'energy8/D' )
    tree.Branch ( 'T'  , v_T  , 'T/D'  )

    tree.Branch ( 'start0' , v_start0 , 'start0/D' )
    tree.Branch ( 'start1' , v_start1 , 'start1/D' )
    tree.Branch ( 'start2' , v_start2 , 'start2/D' )
    tree.Branch ( 'start3' , v_start3 , 'start3/D' )
    tree.Branch ( 'start4' , v_start4 , 'start4/D' )
    tree.Branch ( 'start5' , v_start5 , 'start5/D' )
    tree.Branch ( 'start6' , v_start6 , 'start6/D' )
    tree.Branch ( 'start7' , v_start7 , 'start7/D' )
    tree.Branch ( 'start8' , v_start8 , 'start8/D' )

    tree.Branch ( 'end0' , v_end0 , 'end0/D' )
    tree.Branch ( 'end1' , v_end1 , 'end1/D' )
    tree.Branch ( 'end2' , v_end2 , 'end2/D' )
    tree.Branch ( 'end3' , v_end3 , 'end3/D' )
    tree.Branch ( 'end4' , v_end4 , 'end4/D' )
    tree.Branch ( 'end5' , v_end5 , 'end5/D' )
    tree.Branch ( 'end6' , v_end6 , 'end6/D' )
    tree.Branch ( 'end7' , v_end7 , 'end7/D' )
    tree.Branch ( 'end8' , v_end8 , 'end8/D' )

    tree.Branch ( 'xCSC' , v_xCSC , 'xCSC/D' )
    tree.Branch ( 'yCSC' , v_yCSC , 'yCSC/D' )
    tree.Branch ( 'zCSC' , v_zCSC , 'zCSC/D' )

    for event in range ( 7000 ) :

        gen_tree.GetEntry( event )
        out_tree.GetEntry( event )
        csc_tree.GetEntry( event )


        v_THETAp[0]  = gen_tree.THETAp
        v_THETAe[0]  = gen_tree.THETAe
        v_PHIp[0]    = gen_tree.PHIp
        v_PHIe[0]    = gen_tree.PHIe
        v_Tp[0]      = gen_tree.Tp
        v_Ee[0]      = gen_tree.Ee
        v_xpos[0]    = gen_tree.xPOS
        v_ypos[0]    = gen_tree.yPOS
        v_zpos[0]    = gen_tree.zPOS

        v_peak0[0]   = out_tree.peak0
        v_peak1[0]   = out_tree.peak1
        v_peak2[0]   = out_tree.peak2
        v_peak3[0]   = out_tree.peak3
        v_peak4[0]   = out_tree.peak4
        v_peak5[0]   = out_tree.peak5
        v_peak6[0]   = out_tree.peak6
        v_peak7[0]   = out_tree.peak7
        v_peak8[0]   = out_tree.peak8

        v_energy0[0] = out_tree.energy0
        v_energy1[0] = out_tree.energy1
        v_energy2[0] = out_tree.energy2
        v_energy3[0] = out_tree.energy3
        v_energy4[0] = out_tree.energy4
        v_energy5[0] = out_tree.energy5
        v_energy6[0] = out_tree.energy6
        v_energy7[0] = out_tree.energy7
        v_energy8[0] = out_tree.energy8
        v_T[0]  = out_tree.energy

        v_start0[0]  = out_tree.start0
        v_start1[0]  = out_tree.start1
        v_start2[0]  = out_tree.start2
        v_start3[0]  = out_tree.start3
        v_start4[0]  = out_tree.start4
        v_start5[0]  = out_tree.start5
        v_start6[0]  = out_tree.start6
        v_start7[0]  = out_tree.start7
        v_start8[0]  = out_tree.start8

        v_end0[0]    = out_tree.end0
        v_end1[0]    = out_tree.end1
        v_end2[0]    = out_tree.end2
        v_end3[0]    = out_tree.end3
        v_end4[0]    = out_tree.end4
        v_end5[0]    = out_tree.end5
        v_end6[0]    = out_tree.end6
        v_end7[0]    = out_tree.end7
        v_end8[0]    = out_tree.end8

        v_xCSC[0]    = csc_tree.xCSC
        v_yCSC[0]    = csc_tree.yCSC
        v_zCSC[0]    = 851.6

        tree.Fill()

    root_file.Write()

