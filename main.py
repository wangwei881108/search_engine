#!/usr/bin/python
import urllib2
from collections import defaultdict

def get_page(url):
    try:
        return urllib2.urlopen(url).read()
    except:
        return ""

def get_all_links(content):
    links=[]
    url, end_quote = get_next_target(content)
    content = content[end_quote:]
    if url[0:4] == "http":
        links.append(url)
    
    while(len(url) !=0):
        url, end_quote=get_next_target(content)
        content = content[end_quote:]
        if url[0:4] == "http":
            #  print url
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

def add_to_index(index, link, keyword):
    for word in keyword:
        if (link not in index[word]):
            index[word].append(link)

def add_page_to_index(index, link, content):
    tempkey = content.split()
    keyword = []
    for word in tempkey:
        if(word not in keyword):
            keyword.append(word)
    add_to_index(index, link, keyword)


def union(outlinks, to_crawl):
    to_crawl.extend(outlinks)

def compute_ranks(graph):



count = 0
seed = "https://www.lri.fr"
to_crawl=[]
to_crawl.append(seed)
index = defaultdict(list)
crawled=[]
graph = defaultdict(list)

while (len(to_crawl) != 0):
    if count > 10:
        break
    link = to_crawl.pop(0)
    print "I am here"
    print link
    content = get_page(link)
    outlinks = get_all_links(content)
    add_page_to_index(index, link, content)
    union(outlinks, to_crawl)
    crawled.append(link)
    graph[link].extend(outlinks)
    count += 1



