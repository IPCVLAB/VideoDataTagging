import sys
sys.path.append("C:/Users/mcb/Anaconda3")
sys.path.append("C:/Users/mcb/Anaconda3/Lib/site-packages")

from selenium import webdriver
from bs4 import BeautifulSoup
import requests
# -*- coding: utf-8 -*- 
import operator
import re
import GoogleImageSearch as GS
def get_html(url):
    _html = ""
    resp = requests.get(url)
    if resp.status_code == 200:
        _html = resp.text
        return _html

def Test() :
	#webdriver용 옵션. chrome창이 켜지지 않고 진행됨
	options = webdriver.ChromeOptions()
	options.add_argument("headless")
	options.add_argument('window-size=1920x1080')
	options.add_argument("disable-gpu")
	driver = webdriver.Chrome('.\\chromedriver.exe', chrome_options=options)
	
	
	#url 적용해서 검색    
	url = GS.GetGoogleImageSearchUrl("./Result/copy_0.png");
	driver.get(url)
	driver.find_element_by_xpath('//*[@id="imagebox_bigimages"]/g-section-with-header/div[1]/h3/a').click()
	driver.implicitly_wait(3)
	html = get_html(driver.current_url)
	#pictures = driver.find_elements_by_xpath('//*[@id="rg_s"]/div')[:100]
	soup = BeautifulSoup(html,'lxml')
	
	#크롤링 데이터 추출
	list = soup.find('table',{'class':'images_table'}).findAll('td')
	dict={}
	for line in list:
	    line = str(line)
	    line = (line.split('<br/>'))[-2]
	    line = line.replace('<b>',"")
	    line = line.replace('</b>',"")
	    line = line.split()
	    for word in line:
	        if not re.match("\w",word): #특수문자 예외처리
	            continue
	
	        if word not in dict:
	            dict[word]=1
	        else:
	            dict[word]+=1
	dict = sorted(dict.items(), key=operator.itemgetter(1) , reverse=True)
	list_name = []
	list_val = []
	for word in dict:
	    if(word[1] > 4) :	        
	        list_name.append(word[0])

	for word in dict:
	    if(word[1] > 4) :	        
	        list_val.append(str(word[1]))

	return_list = list_name + list_val
	return return_list