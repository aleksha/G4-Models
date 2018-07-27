convert -limit memory 2MB  -fuzz 1%  -delay 1 disp_04*.png -coalesce  -layers OptimizeTransparency wanim4.gif
convert -fuzz 1% -delay 1x24 temp_*.png -coalesce -layers OptimizeTransparency animation.gif;
convert  -limit memory 2MB wanim0.gif wanim1.gif wanim2.gif wani m3.gif wanim4.gif zzz.gif
