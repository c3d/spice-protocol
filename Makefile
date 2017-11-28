BUILD=../build/

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
	start-packed.h		\
	stats.h			\
	types.h			\
	vd_agent.h		\
	vdi_dev.h

HDR_INSTALL=$(SPICE_HEADERS:%=spice/%)
PREFIX_HDR=$(PREFIX)include/spice-1/spice/

include $(BUILD)rules.mk
