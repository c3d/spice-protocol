MIQ=make-it-quick/

SPICE_HEADERS=			\
	barrier.h		\
	controller_prot.h	\
	end-packed.h		\
	enums.h			\
	error_codes.h		\
	foreign_menu_prot.h	\
	ipc_ring.h		\
	macros.h		\
	protocol.h		\
	qxl_dev.h		\
	qxl_windows.h		\
	stream-device.h		\
	start-packed.h		\
	stats.h			\
	types.h			\
	vd_agent.h		\
	vdi_dev.h

PACKAGE_NAME=spice-protocol
PACKAGE_VERSION=0.12.14
PACKAGE_DESCRIPTION=SPICE protocol
PACKAGE_URL=https://spice-space.org
PACKAGE_REQUIRES=
PACKAGE_BUGS=spice-devel@lists.freedesktop.org
PACKAGE_PREFIX_HDR=$(PREFIX)include/spice-1/


HDR_INSTALL=$(SPICE_HEADERS:%=spice/%)
PREFIX_HDR=$(PREFIX)include/spice-1/spice/

include $(MIQ)rules.mk

$(MIQ)rules.mk:
	git clone https://github.com/c3d/make-it-quick
