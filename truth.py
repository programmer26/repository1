import mosspy

userid = 751640219

m = mosspy.Moss(userid, "c")

#m.addBaseFile("ls.c")
#m.addBaseFile("watch.c")

# Submission Files
m.addFile("test1.c")
m.addFile("test2.c")

# progress function optional, run on every file uploaded
# result is submission URL
url = m.send(lambda file_path, display_name: print('*', end='', flush=True))
print()

print ("Report Url: " + url)

# Save report file
#m.saveWebPage(url, "submission/report.html")

# Download whole report locally including code diff links
#mosspy.download_report(url, "submission/report/", connections=8, log_level=10, on_read=lambda url: print('*', end='', flush=True)) 
# log_level=logging.DEBUG (20 to disable)
# on_read function run for every downloaded file

