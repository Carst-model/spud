#!/usr/bin/env python

#    This file is part of Diamond.
#
#    Diamond is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Diamond is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Diamond.  If not, see <http://www.gnu.org/licenses/>.

import gobject
import gtk

import attributewidget
import databuttonswidget
import datawidget

class SliceView(gtk.Window):
  
  __gsignals__ = { "on-store" : (gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE, ()),
                   "update-name"  : (gobject.SIGNAL_RUN_LAST, gobject.TYPE_NONE, ())}

  def __init__(self, parent):
    gtk.Window.__init__(self)
    
    self.set_title("Slice View")
    self.set_modal(True)
    self.set_transient_for(parent)

    mainvbox = gtk.VBox()
    self.vbox = gtk.VBox()

    scrolledWindow = gtk.ScrolledWindow()
    scrolledWindow.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
    scrolledWindow.add_with_viewport(self.vbox)

    self.databuttons = databuttonswidget.DataButtonsWidget()

    self.statusbar = gtk.Statusbar()

    mainvbox.pack_start(scrolledWindow)
    mainvbox.pack_start(self.databuttons)
    mainvbox.pack_start(self.statusbar)

    self.add(mainvbox)
    self.show_all()

  def update(self, node, tree):
    for n in self.get_nodes(node, tree):
      self.vbox.pack_start(self.control(node))

  def get_nodes(self, node, tree):
    return [node]

  def control(self, node):
    hbox = gtk.HBox()

    label = gtk.Label(node.name)

    data = datawidget.DataWidget()
    data.geometry_dim_tree = self.geometry_dim_tree
    data.connect("on-store", self.on_store)
    data.set_buttons(self.databuttons)
    data.update(node)

    attributes = attributewidget.AttributeWidget()
    attributes.connect("on-store", self.on_store)
    attributes.connect("update-name", self.update_name)
    attributes.update(node)

    hbox.pack_start(label)
    hbox.pack_start(data)
    hbox.pack_start(attributes)
    
    hbox.show_all()

    return hbox

  def on_store(self, widget = None):
    self.emit("on-store")

  def update_name(self, widget = None):
    self.emit("update-name") 

gobject.type_register(SliceView)
