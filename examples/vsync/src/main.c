#include <seven/prelude.h>
#include <seven/hw/video/memory.h>

void vblank_callback(u16 irqs)
{
    (void)irqs;

    BG_PALETTE[0] += 1;
}

int main(void)
{
    // Set up the necessary interrupt handling
    irqInitDefault();
    irqEnable(IRQ_VBLANK);
    irqHandlerSet(IRQ_VBLANK, vblank_callback);

    // Clear the force-blank bit
    REG_DISPCNT = 0;
    REG_DISPSTAT = LCD_VBLANK_IRQ_ENABLE;

    while (1)
    {
        // Wait for V-sync
        biosVBlankIntrWait();
    }
}
