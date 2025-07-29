SUMMARY = "vSomeIP Server Application"
LICENSE = "CLOSED"

SRC_URI = "git://github.com/PatrickAtef8/vsomeip_work.git;branch=master;protocol=https \
           file://vsomeip-server.service"
SRCREV = "dc2f27b3799c0b47837b9c74d99fecef4a3dd186"


S = "${WORKDIR}/git/02-ClientServerRPC"

inherit cmake systemd

DEPENDS += "vsomeip boost"

RDEPENDS:${PN} += "vsomeip boost-filesystem boost-system boost-thread"

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "vsomeip-server.service"

EXTRA_OECMAKE += "-DCMAKE_BUILD_TYPE=Release"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/server ${D}${bindir}/server

    install -d ${D}${systemd_unitdir}/system
    install -m 0644 ${WORKDIR}/vsomeip-server.service ${D}${systemd_unitdir}/system/vsomeip-server.service

    install -d ${D}${sysconfdir}/vsomeip
    install -m 0644 ${S}/server.json ${D}${sysconfdir}/vsomeip/server.json
}

FILES:${PN} += "${bindir}/server ${systemd_unitdir}/system/vsomeip-server.service ${sysconfdir}/vsomeip/server.json"
