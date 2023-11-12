#include <libusb-1.0/libusb.h>
#include <cstdio>
#include <map>
#include <iostream>
using std::map;
using std::string;

map<int, string> usbClasses = {
        {1, "аудио"},
        {2, "коммуникационное устройство"},
        {3, "устройство пользовательского интерфейса"},
        {5, "физическое устройство"},
        {6, "изображение"},
        {7, "принтер"},
        {8, "устройство хранения данных"},
        {9, "hub"},
        {10, "CDC-Data"},
        {11, "Smart card"},
        {13, "Content Security"},
        {14, "видеоустройство"},
        {15, "персональное медицинское устройство"},
        {16, "аудио- и видеоустройства"},
        {17, "Класс устройства Billboard"},
        {18, "USB Type-C Bridge Class"},
        {220, "диагностическое устройство"},
        {224, "беспроводный контроллер"},
        {239, "различные устройства"},
        {254, "специфическое устройство"}
};

static void printDevs(libusb_device **devs, ssize_t amount)
{
    libusb_device *dev;
    for (ssize_t i = 0; i < amount; i++) {
        printf("\nустройство %ld:\n", i + 1);
        dev = devs[i];
        libusb_device_descriptor desc{};
        libusb_device_handle* handle = nullptr;
        int ret;
        unsigned char string[256];
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor\n");
            return;
        }
        uint8_t classDev = desc.bDeviceClass;
        if (classDev == 0) {
            libusb_config_descriptor *config;
            libusb_get_config_descriptor(dev, 0, &config);
            const libusb_interface *interface = &config->interface[0];
            const libusb_interface_descriptor *interfaceDescriptor = &interface->altsetting[0];
            classDev = interfaceDescriptor->bInterfaceClass;
        }
        uint8_t idVendor = desc.idVendor;
        uint8_t idProduct = desc.idProduct;
        ret = libusb_open(dev, &handle);
        if (LIBUSB_SUCCESS == ret) {
            printf("device class: %d (%s)\nvendor id: %d\nproduct id: %d\n", classDev, usbClasses[classDev].c_str(), idVendor, idProduct);
            printf("product: ");
            ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, string, sizeof(string));
            if (ret > 0) {
                printf("%s\n", string);
            } else {
                printf("not found\n");
            }
            printf("serial number: ");
            ret = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, string, sizeof(string));
            if (ret > 0) {
                printf("%s\n", string);
            } else {
                printf("not found\n");
            }
        }
    }
}
int main(void) {
    libusb_device **devs;
    libusb_context *ctx = nullptr;
    int r = libusb_init(&ctx);
    if (r < 0)
        return r;
    ssize_t cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0){
        libusb_exit(ctx);
        return (int) cnt;
    }
    printDevs(devs, cnt);
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
    return 0;
}