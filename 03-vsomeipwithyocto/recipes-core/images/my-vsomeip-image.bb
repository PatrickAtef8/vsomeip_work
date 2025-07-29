SUMMARY = "A minimal image with vSomeIP and a server application" 
LICENSE = "CLOSED"

inherit core-image

IMAGE_FEATURES += "splash ssh-server-dropbear package-management"

IMAGE_INSTALL:append =" vsomeip vsomeip-server systemd systemd-analyze connman-client bash"

IMAGE_ROOTFS_EXTRA_SPACE = "5242880"