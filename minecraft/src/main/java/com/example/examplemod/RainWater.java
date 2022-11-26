package com.example.examplemod;

import net.minecraft.world.entity.Entity;
import net.minecraft.world.level.Explosion;
import net.minecraft.world.level.Level;
import net.minecraftforge.event.entity.living.LivingEvent;
import net.minecraftforge.eventbus.api.SubscribeEvent;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.Random;

public class RainWater {
    private static final Logger LOGGER = LogManager.getLogger();
	private static final double HIGH_HUMIDITY = 95;
    @SubscribeEvent
    public void makeWater(LivingEvent.LivingTickEvent event) {
        Entity entity = event.getEntity();

		try {
			Level world = entity.getCommandSenderWorld();
			if(SensorsListener.lastHumidity>HIGH_HUMIDITY ||
					SoundListener.lastNote.equals("g")) {
				world.setRainLevel(new Random().nextFloat());
				world.setThunderLevel(new Random().nextFloat());
				world.createFireworks(entity.getX(), entity.getY(), entity.getZ(), 100.5, 100.5, 10.4, null);
			}
			else {
				world.setRainLevel(0);
				world.setThunderLevel(0);
			}
			if(SoundListener.lastNote.equals("a")) {
				world.setRainLevel(0);
				world.setThunderLevel(0);
			}
		} catch (Exception e) {
			LOGGER.error("Turning rain on", e);
		}
  }
}