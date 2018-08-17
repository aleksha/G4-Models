host  = "\"https://aleksha.space/event/"
fname = "view.html"
import os

html_output = open(fname,"w")

ss = "<html>\n<head>\n\t<title>Display</title></head><body>"
html_output.write(ss)

for f in os.listdir("./"):
    end_of_filename = f[-4:]
    if end_of_filename == ".png":
        ss = "<a href=" + host + f + "\">"+f+"</a><br><br>"
        html_output.write(ss)

ss =   "</body></html>"
html_output.write(ss)

html_output.close()
