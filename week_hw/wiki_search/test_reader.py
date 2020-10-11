import bz2
import xml.etree.ElementTree as ET
import wikitextparser as wtp
import sqlite3 as sql
import zlib
import attributes

conn = sql.connect('connect3.db')
c = conn.cursor()
#c.execute('CREATE TABLE people2 (name, male, has_spouse, shows_spouse, spouse)') #how to verify people with same name? (use links somehow?)
c.execute('''
CREATE TABLE IF NOT EXISTS all_pages(
pageid integer,
name text,
article text,
categories text)''')
conn.commit()


file_name = "enwiki-20200901-pages-articles-multistream.xml.bz2"
test_file = "test.xml"


def getCategories(text):
  parsed = wtp.parse(text)
  s = parsed.get_sections()[-1].string
  categories = s[s.find("[[Category:"):].split("\n")
  return categories

def living(text):
  parsed = wtp.parse(text)
  for link in parsed.wikilinks:
    if(link.title.lower().strip() == "category:living people"):
      #print("living person")
      return True
  return False


  
def exclude(elem):
  if elem.find('redirect') != None:
    return True
  if elem.find('ns') == None or elem.find('ns').text != '0':
    return True
  return False
  
def iterate_page(elem):
  name = elem.find('title').text
  #spouse = get_spouse(str(elem2.text))
  #male = gender(str(elem2.text))
  pageid = elem.find('id').text
  page = str(elem.find('revision/text').text)
  categories = getCategories(page)
  #infobox = get_infobox(page)
  
  #print(pageid)
  #print(page)
  #print(categories)
  #print(infobox)
  
  #print(categories)
  is_living = '[[Category:Living people]]' in categories
  if(is_living):
    zpage = zlib.compress(page.encode('utf-8'))
    c.execute("INSERT INTO all_pages VALUES (?, ?, ?, ?)", (pageid, name, zpage, repr(categories)))

  return is_living
  
def iterate_redirect(elem):
  for elem2 in elem.iter():
    print(elem2.tag, elem2)

def is_redirect(elem):
  return elem.find('redirect') != None

def iterate_file2(file_name):
  page_count = 0
  living_count = 0
  start = False
  for event, elem in ET.iterparse(file_name, events = ('end',)):
    
    elem.tag = elem.tag.split('}')[-1] #last element after '}'
    if elem.tag == 'page':
      page_count += 1
      if(page_count % 100 == 0):
        print(start, page_count)
      if(is_redirect(elem)):
          print("redirect: ")
          iterate_redirect(elem)
      if(start):
        if(is_redirect(elem)):
          iterate_redirect(elem)
        else:
          iterate_page(elem)
      else:
        id = elem.find('id').text
        print("id:", id)
        if(id == '19320409'):
          start = True
      elem.clear()
        
  
          
def iterate_file(file_name):
  page_count = 0
  living_count = 0
  for event, elem in ET.iterparse(file_name, events = ('end',)):
    elem.tag = elem.tag.split('}')[-1] #last element after '}'
    if elem.tag == 'page':
      #iterate through that page
      if(not exclude(elem)):
        if iterate_page(elem):
          living_count += 1
          print('living:', living_count)
        page_count += 1
        if(page_count%100 == 0):
          print("pages:", page_count)
          conn.commit()
      elem.clear() #because iterating through entire document, entire document is stored under root node (must clear other nodes before moving on)


def print_all_pages():
  for (pageid, name, article, categories) in c.execute("SELECT * FROM all_pages"):
    print(pageid, name)

def print_table():
  c2.execute('''
  CREATE TABLE IF NOT EXISTS final_data(
  pageid integer,
  name text,
  gender integer,
  shows_spouse integer,
  spouses text)''')
  #gender value: 0 = female, 1 = male
  #shows_spouse values: -2 = no infobox, -1 = infobox, no spouse, 0 = spouse, no link, number of spouses = link
  conn2.commit()
  commit_num = 0
  for(pageid, name, article, categories) in c.execute("SELECT * FROM all_pages"):
    print(pageid, name)
    article = zlib.decompress(article).decode('utf-8')
    #spouse
    spouse_val = 0
    spouses = []
    infobox_args = attributes.get_infobox(article)
    if(infobox_args != None):
      spouse = attributes.get_spouse(infobox_args)
      if(spouse != None):
        spouses = attributes.spouse_names(spouse)
        spouse_val = len(spouses)
      else:
        spouse_val = -1
    else:
      spouse_val = -2
      
    #gender
    gender = attributes.gender(article)
    
    #name
    new_name = attributes.clean_name(name)
    
    #insert
    c2.execute("INSERT INTO final_data VALUES (?, ?, ?, ?, ?)", (pageid, new_name, gender, spouse_val, repr(spouses)))
    #print(pageid, name, gender, spouse_val, spouses)
    commit_num += 1
    if(commit_num%100 == 0):
      conn2.commit()


#print_all_pages()
conn2 = sql.connect('connect4.db')
c2 = conn2.cursor()

xml_file = bz2.open(file_name)
iterate_file2(xml_file)

#c2.execute("DROP table final_data")
#conn.commit()
#print_table()
#conn.commit()


