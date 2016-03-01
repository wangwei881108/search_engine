#!/usr/bin/python
import urllib2

def get_page(url):
    try:
        return urllib2.urlopen(url).read()
    except:
        return ""

def get_all_links(content):
    links=[]
    url, end_quote = get_next_target(content)
    content = content[end_quote:]
    links.append(url)
    
    while(len(url) !=0):
        url, end_quote=get_next_target(content)
        print url
        content = content[end_quote:]
        links.append(url)
    
    return links

def get_next_target(content):
    location = content.find("<a href=")
    if(location!=-1):
        start_quote = location
        comma1 = content.find('"', start_quote)
        end_quote = content.find('"', comma1+1)
        url = content[comma1+1:end_quote]
    else:
        url = ""
        end_quote = 0
    return url, end_quote

def add_page


content = get_page("https://www.lri.fr")
links = get_all_links(content)
