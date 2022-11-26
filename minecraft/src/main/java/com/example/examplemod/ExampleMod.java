package com.example.examplemod;

import com.mojang.logging.LogUtils;
import net.minecraft.client.Minecraft;
import net.minecraft.server.MinecraftServer;
import net.minecraft.world.item.BlockItem;
import net.minecraft.world.item.CreativeModeTab;
import net.minecraft.world.item.Item;
import net.minecraft.world.item.ItemStack;
import net.minecraft.world.item.enchantment.EnchantmentHelper;
import net.minecraft.world.item.enchantment.Enchantments;
import net.minecraft.world.level.block.Block;
import net.minecraft.world.level.block.Blocks;
import net.minecraft.world.level.block.state.BlockBehaviour;
import net.minecraft.world.level.material.Material;

import net.minecraftforge.common.MinecraftForge;
import net.minecraftforge.event.level.BlockEvent;
import net.minecraftforge.eventbus.api.EventPriority;
import net.minecraftforge.eventbus.api.IEventBus;
import net.minecraftforge.eventbus.api.SubscribeEvent;
import net.minecraftforge.fml.InterModComms;
import net.minecraftforge.fml.common.Mod;
import net.minecraftforge.fml.event.lifecycle.FMLClientSetupEvent;
import net.minecraftforge.fml.event.lifecycle.FMLCommonSetupEvent;
import net.minecraftforge.fml.event.lifecycle.InterModEnqueueEvent;
import net.minecraftforge.fml.event.lifecycle.InterModProcessEvent;
import net.minecraftforge.event.server.ServerStartingEvent;
import net.minecraftforge.fml.javafmlmod.FMLJavaModLoadingContext;
import net.minecraftforge.registries.DeferredRegister;
import net.minecraftforge.registries.ForgeRegistries;
import net.minecraftforge.registries.RegistryObject;
import net.minecraftforge.server.ServerLifecycleHooks;
import org.slf4j.Logger;
import com.amazonaws.services.iot.client.AWSIotMqttClient;
import com.amazonaws.services.iot.client.AWSIotQos;
import com.amazonaws.services.iot.client.AWSIotTopic;
import com.amazonaws.services.iot.client.sample.sampleUtil.SampleUtil;

// The value here should match an entry in the META-INF/mods.toml file
@Mod(ExampleMod.MODID)
public class ExampleMod
{
    AWSIotMqttClient client = null;

    public static final String AWS_IOT_TOPIC1 = "playground/relay";
    public static final String AWS_IOT_TOPIC2 = "playground2/relay";
    // public static final String AWS_IOT_ENDPOINT = "<prefix>-ats.iot.<region>.amazonaws.com";

    public static final String AWS_IOT_ENDPOINT = "a2p4fyajwx9lux-ats.iot.us-east-1.amazonaws.com";
    public static final String AWS_IOT_CLIENT_ID = "jump-mod";
    public static final String AWS_IOT_CERTIFICATE_FILE = "/home/vsenger/minecraft-iot/8f2b2f776911332a0fea819064421830e592b55f32c4a6262918700841fc5c32-certificate.pem.crt";
    public static final String AWS_IOT_PRIVATE_KEY_FILE = "/home/vsenger/minecraft-iot/8f2b2f776911332a0fea819064421830e592b55f32c4a6262918700841fc5c32-private.pem.key";

    private static final String AWS_IOT_INBOUND_TOPIC = "playground/sensors";
    private static final AWSIotQos AWS_IOT_INBOUND_TOPIC_QOS = AWSIotQos.QOS0;
    private static final String AWS_IOT_SENSORS = "playground/sensors";

    private static final String AWS_IOT_SOUND = "playground/sound";
    // Define mod id in a common place for everything to reference
    public static final String MODID = "examplemod";
    // Directly reference a slf4j logger
    private static final Logger LOGGER = LogUtils.getLogger();
    // Create a Deferred Register to hold Blocks which will all be registered under the "examplemod" namespace
    public static final DeferredRegister<Block> BLOCKS = DeferredRegister.create(ForgeRegistries.BLOCKS, MODID);
    // Create a Deferred Register to hold Items which will all be registered under the "examplemod" namespace
    public static final DeferredRegister<Item> ITEMS = DeferredRegister.create(ForgeRegistries.ITEMS, MODID);

    // Creates a new Block with the id "examplemod:example_block", combining the namespace and path
    public static final RegistryObject<Block> EXAMPLE_BLOCK = BLOCKS.register("example_block", () -> new Block(BlockBehaviour.Properties.of(Material.STONE)));
    // Creates a new BlockItem with the id "examplemod:example_block", combining the namespace and path
    public static final RegistryObject<Item> EXAMPLE_BLOCK_ITEM = ITEMS.register("example_block", () -> new BlockItem(EXAMPLE_BLOCK.get(), new Item.Properties().tab(CreativeModeTab.TAB_BUILDING_BLOCKS)));

    public ExampleMod()
    {
        IEventBus modEventBus = FMLJavaModLoadingContext.get().getModEventBus();

        // Register the commonSetup method for modloading
        modEventBus.addListener(this::commonSetup);

        // Register the Deferred Register to the mod event bus so blocks get registered
        BLOCKS.register(modEventBus);
        // Register the Deferred Register to the mod event bus so items get registered
        ITEMS.register(modEventBus);

        // Register ourselves for server and other game events we are interested in
        MinecraftForge.EVENT_BUS.register(this);
        MinecraftForge.EVENT_BUS.register(new RainWater());

    }

    private void commonSetup(final FMLCommonSetupEvent event)
    {
        String clientEndpoint = AWS_IOT_ENDPOINT;
        String clientId = AWS_IOT_CLIENT_ID;
        String certificateFile = AWS_IOT_CERTIFICATE_FILE;
        String privateKeyFile = AWS_IOT_PRIVATE_KEY_FILE;

        SampleUtil.KeyStorePasswordPair pair = SampleUtil.getKeyStorePasswordPair(certificateFile, privateKeyFile);
        this.client = new AWSIotMqttClient(clientEndpoint, clientId, pair.keyStore, pair.keyPassword);
        LOGGER.info("AWS IoT Core Setup");

        try {
            client.connect();
            LOGGER.info("AWS IoT Core Connected!");

            MinecraftServer currentServer = ServerLifecycleHooks.getCurrentServer();
            //currentServer.getWo
            // https://github.com/aws/aws-iot-device-sdk-java/tree/master/aws-iot-device-sdk-java-samples/src/main/java/com/amazonaws/services/iot/client/sample/pubSub

            AWSIotTopic sensorsListener = new SensorsListener(AWS_IOT_SENSORS, AWS_IOT_INBOUND_TOPIC_QOS, currentServer);
            AWSIotTopic soundListener = new SoundListener(AWS_IOT_SOUND, AWS_IOT_INBOUND_TOPIC_QOS, currentServer);
            client.subscribe(sensorsListener, true);
            client.subscribe(soundListener, true);

        } catch (Exception e) {
            LOGGER.error("Error connecting to IoT", e);
        }

        // Some common setup code
        LOGGER.info("HELLO FROM COMMON SETUP");
        LOGGER.info("DIRT BLOCK >> {}", ForgeRegistries.BLOCKS.getKey(Blocks.DIRT));
    }

    // You can use SubscribeEvent and let the Event Bus discover methods to call
    @SubscribeEvent
    public void onServerStarting(ServerStartingEvent event)
    {
        // Do something when the server starts
        LOGGER.info("HELLO from server starting");
    }

    // You can use EventBusSubscriber to automatically register all static methods in the class annotated with @SubscribeEvent
    @Mod.EventBusSubscriber(modid = MODID, bus = Mod.EventBusSubscriber.Bus.MOD)
    public static class ClientModEvents
    {
        @SubscribeEvent
        public static void onClientSetup(FMLClientSetupEvent event)
        {
            // Some client setup code
            LOGGER.info("HELLO FROM CLIENT SETUP");
            LOGGER.info("MINECRAFT NAME >> {}", Minecraft.getInstance().getUser().getName());
        }
    }
    @SubscribeEvent(priority = EventPriority.LOWEST)
    public static void onBlockBreak(BlockEvent.BreakEvent event) {
        if(event.getPlayer() == null) return;

        ItemStack usedItem = event.getPlayer().getItemInHand(event.getPlayer().getUsedItemHand());
        if(usedItem == null) return;

    }
    int lamp =0, lamp_state=0;
    @SubscribeEvent
    public void blockBreak(BlockEvent.BreakEvent event) {
        LOGGER.info("Block break");

        try {
            lamp_state = lamp_state == 0 ? 1 : 0;
            client.publish(ExampleMod.AWS_IOT_TOPIC1 , "" + lamp_state);

            //client.publish(lamp==0 ? ExampleMod.AWS_IOT_TOPIC1 : ExampleMod.AWS_IOT_TOPIC2, "" + lamp_state);
            //if(lamp_state==0) lamp = lamp == 0 ? 1 : 0;
        } catch (Exception e) {
            LOGGER.error("Error publishing event to IoT", e);
        }
    }

}
