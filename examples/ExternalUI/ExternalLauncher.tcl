###################################
# External UI example with Tcl/Tk #
##################################

# open the Fifo, and delete the file
set fifoPath [lindex $::argv 0]
set fifoChannel [open $fifoPath r+]
file delete $fifoPath

# set window title and size
wm title . ExternalExampleUI
wm maxsize . [lindex $::argv 1] [lindex $::argv 2]

# install the command receiver
set scriptData {}

proc scriptDataArrived {} {
    set byte [read $::fifoChannel 1]
    if {$byte eq "\x00"} {
        eval $::scriptData
        set ::scriptData {}
    } else {
        append ::scriptData $byte
    }
}

fileevent $::fifoChannel readable {scriptDataArrived}

# define command handlers
proc pluginParameterChanged {index value} {
    .textedit insert end "Receive Parameter: index=$index value=$value\n"
}

# lay out the elements
label .hello -text {This is the External UI example with Tcl/Tk.}
pack .hello -side top
text .textedit
pack .textedit -side top
