#!/usr/bin/python

# it is recommended to use python installed from brew on os x
import argparse
import string
import os
# import ntpath
from datetime import datetime


try:
    from lxml import etree
    import lxml.builder as builder
    print("running with lxml.etree")

except ImportError:
    print("Failed to import lxml.etree")
    quit()

parser = argparse.ArgumentParser(description="AppCast updater argument parser")
parser.add_argument("-a", "--appcast", help="path to updating appcast xml file", required=True)
parser.add_argument("-c", "--changes", help="path to new changes file", required=True)
parser.add_argument("-r", "--relnotes", help="path to updating relnotes html file", required=True)
parser.add_argument("-v", "--version", help="version number", required=True)
parser.add_argument("-d", "--distrib", help="path to distribution file", required=True)

args = parser.parse_args()

print "Appcast to update: " + args.appcast
print "New changes file: " + args.changes
print "Relnotes to update: " + args.relnotes

if not os.path.isfile(args.distrib):
    print "No reference to distrib file"
    quit()

print "Path to distribution is " + args.distrib
print



# Read relnotes text
print "Reading relnotes"

relnotesFile = open(args.relnotes, "r")
relnotesText = relnotesFile.read()
relnotesFile.close()

# Read changes file
print "Reading changes"
changesFile = open(args.changes, "r")
changesText = changesFile.read()
changesFile.close()

# Add or replace latest changes text into relnotes file.
versionBeginText = "<!-- begin version=" + args.version + " -->"
versionEndText = "<!-- end version=" + args.version + " -->"

versionBeginIndex = relnotesText.find(versionBeginText)
versionEndIndex = relnotesText.find(versionEndText)

newChangeText = versionBeginText +"\r\n" + changesText + "\r\n" + versionEndText
bodyStart = relnotesText.find("<body>")

# Dump <body> position
# print "Tag <body> found at " + str(bodyStart) + " position."

# If this version text boundary is not found
if versionBeginIndex == -1 & versionEndIndex == -1:
    print "Version " + args.version + " is not found, inserting new one."
    relnotesText = relnotesText[:bodyStart+7] + "\r\n" + newChangeText + "\r\n" + relnotesText[bodyStart+7:]
else:
    print "Version " + args.version + " is found, updating."
    relnotesText = relnotesText[:versionBeginIndex] + newChangeText + relnotesText[versionEndIndex + len(versionEndText):]

relnotesFile = open(args.relnotes, "w")
relnotesFile.write(relnotesText)
relnotesFile.close()

print "Relnotes updated"

# Read appcast file
print "Read appcast file"
appCastFile = open(args.appcast, "r")
appCastText = appCastFile.read()
appCastFile.close()

RELEASENOTESLINK = "http://satorilight.com/releasenotes.html"

# Parse & update appcast
print "Parse appcast file"
root = etree.XML(appCastText)
# print etree.tostring(root)

# Find /rss/channel/item/enclosure/sparkle:version=version
# If not found - create new item
xmlNamespaces = {'atom': 'http://www.w3.org/2005/Atom',
                 'sparkle': 'http://www.andymatuschak.org/xml-namespaces/sparkle',
                 'fervor': 'https://github.com/pypt/fervor',
                 'dc': 'http://purl.org/dc/elements/1.1/'}

xpathQuery = "/rss/channel/item/enclosure[@sparkle:version=\'" + args.version + "\']"
enclosure = root.xpath(xpathQuery, namespaces=xmlNamespaces)
if len(enclosure) > 0:
    itemElement = enclosure[0].getparent()
    itemElement.getparent().remove(itemElement)

channel = root.xpath("/rss/channel")
if len(channel) == 0:
    print "Bad app cast file"
    quit()

# Get reference to first <channel> tag
channelElement = channel[0]

print "Update appcast file"
# Create new <item> tag
itemElement = etree.SubElement(channelElement, "item", nsmap=xmlNamespaces)

etree.SubElement(itemElement, "title").text = "Version " + args.version
etree.SubElement(itemElement, "pubDate").text = datetime.utcnow().strftime("%a, %d %b %Y %T %z+0000")
etree.SubElement(itemElement, "guid", isPermalink="true").text = RELEASENOTESLINK
etree.SubElement(itemElement, "link").text = RELEASENOTESLINK
etree.SubElement(itemElement, "{http://www.andymatuschak.org/xml-namespaces/sparkle}releaseNotesLink").text = RELEASENOTESLINK

osxEnclosureElement = etree.SubElement(itemElement, "enclosure", nsmap=xmlNamespaces)
osxEnclosureElement.set("url", "http://satorilight.com/downloads/" + os.path.basename(args.distrib))
osxEnclosureElement.set("type", "application/octet-stream")
statinfo = os.stat(args.distrib)
osxEnclosureElement.set("length", str(statinfo.st_size))
osxEnclosureElement.set("{https://github.com/pypt/fervor}platform", "Q_OS_MAC")
osxEnclosureElement.set("{http://www.andymatuschak.org/xml-namespaces/sparkle}version", args.version)
osxEnclosureElement.set("{http://www.andymatuschak.org/xml-namespaces/sparkle}dsaSignature", "0000000000")

print "Produced <item> tag: " + etree.tostring(itemElement, pretty_print=True)

# itemElement refers to current version element
channelElement.insert(5, itemElement)

# Serialize to text
appCastText = etree.tostring(root, pretty_print=True)

appCastFile = open(args.appcast, "w")
appCastFile.write(appCastText)
appCastFile.close()

print "Appcast file updated"

#print "Loading index.html"
#indexFile = open("../site/index.html")
#indexText = indexFile.read()
#indexFile.close()

#print "Updating index.html"

quit()