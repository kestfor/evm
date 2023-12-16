#include "C:/libusb/libusb-1.0.26-binaries/libusb-MinGW-x64/include/libusb-1.0/libusb.h"
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

static void printDevs(libusb_device **devs, const ssize_t amount)
{
    for (ssize_t i = 0; i < amount; i++) {
        printf("\nустройство %ld:\n", i + 1);
        libusb_device *dev = devs[i];
        libusb_device_descriptor desc{};
        libusb_device_handle* handle = nullptr;
        const int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor\n");
            return;
        }
        uint8_t classDev = desc.bDeviceClass;
        if (classDev == 0) {
            constexpr int defaultInd = 0;
            libusb_config_descriptor *config;
            libusb_get_config_descriptor(dev, defaultInd, &config);
            const libusb_interface *interface = &config->interface[defaultInd];
            const libusb_interface_descriptor *interfaceDescriptor = &interface->altsetting[defaultInd];
            libusb_free_config_descriptor(config);
            classDev = interfaceDescriptor->bInterfaceClass;
        }
        int ret = libusb_open(dev, &handle);
        if (LIBUSB_SUCCESS == ret) {
            const uint8_t idVendor = desc.idVendor;
            const uint8_t idProduct = desc.idProduct;
            printf("device class: %d (%s)\nvendor id: %d\nproduct id: %d\n", classDev, usbClasses[classDev].c_str(), idVendor, idProduct);
            printf("product: ");
            unsigned char string[256];
            ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, string, sizeof(string));
            if (ret > 0) {
                printf("%p\n", string);
            } else {
                printf("not found\n");
            }
            printf("serial number: ");
            ret = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, string, sizeof(string));
            if (ret > 0) {
                printf("%p\n", string);
            } else {
                printf("not found\n");
            }
        }
        libusb_close(handle);
    }
}
int main() {
    libusb_device **devs;
    libusb_context *ctx = nullptr;
    const int r = libusb_init(&ctx);
    if (r < 0)
        return r;
    const ssize_t cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0){
        libusb_exit(ctx);
        return static_cast<int>(cnt);
    }
    printDevs(devs, cnt);
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
    return 0;
}