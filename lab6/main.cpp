#include <iostream>
#include <C:\libusb\libusb-1.0.26-binaries\libusb-MinGW-x64\include\libusb-1.0\libusb.h>
#include <stdio.h>
#include <clocale>
#include <vector>
#include <map>
using namespace std;

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

void printdev(libusb_device *dev){
    vector<int> ids;
    libusb_device_descriptor desc; // дескриптор устройства
    libusb_config_descriptor *config; // дескриптор конфигурации объекта
    const libusb_interface *inter;
    const libusb_interface_descriptor *interdesc;
    const libusb_endpoint_descriptor *epdesc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0){
        fprintf(stderr,
                "Ошибка: дескриптор устройства не получен, код: %d.\n",r);
        return;
    }
    libusb_device_handle* handle = nullptr;
    unsigned char str[256] = "";
    int ret = libusb_open(dev, &handle);
    if (LIBUSB_SUCCESS == ret) {
        printf("get %04x:%04x device string descriptor \n", desc.idVendor, desc.idProduct);
    }
    ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, str, 256);
    if (ret > 0) {
        printf("%s\n", str);
    }
    // получить конфигурацию устройства
    libusb_get_config_descriptor(dev, 0, &config);
    cout << "Число конфигураций: " << (int) desc.bNumConfigurations << endl;
    cout << "Класс устройства: " << usbClasses[(int) desc.bDeviceClass] << '\n';
    cout << "id Производителя: " << (int) desc.idVendor << '\n';
    cout << "id устройства: " << (int) desc.idProduct << '\n';
    cout << "количество интерфейсов: " << (int) config->bNumInterfaces << endl;
    for(int i=0; i<(int)config->bNumInterfaces; i++){
        inter = &config->interface[i];
        cout << "интерфейс № " << i + 1 << ":\n";
        cout << '\t' << "число альтернативных настроек: " << inter->num_altsetting << endl;
        for(int j=0; j<inter->num_altsetting; j++) {
            interdesc = &inter->altsetting[j];
            cout << "\t\tальтернативные настройки № " << j + 1 << endl;
            cout << "\t\t" << "номер интерфейса: " << (int) interdesc->bInterfaceNumber << endl;
            cout << "\t\t" << "класс интерфейса: " << usbClasses[(int) interdesc->bInterfaceClass] << endl;
            cout << "\t\t" << "число конечных точек: " << (int) interdesc->bNumEndpoints << endl;
            for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
                cout << "\t\t\tконечная точка № " << k + 1 << ':' << endl;
                cout << "\t\t\tтип дескриптора: " << (int) epdesc->bDescriptorType << endl;
                cout << "\t\t\tадрес конечной точки: " << (int) epdesc->bEndpointAddress << endl;
            }
        }
    }
    libusb_free_config_descriptor(config);
}

int main() {
    setlocale(LC_ALL,"Russian");
    libusb_device **devs; // указатель на указатель на устройство,
    // используется для получения списка устройств
    libusb_context *ctx = nullptr; // контекст сессии libusb
    int r; // для возвращаемых значений
    ssize_t cnt; // число найденных USB-устройств
    ssize_t i; // индексная переменная цикла перебора всех устройств
    // инициализировать библиотеку libusb, открыть сессию работы с libusb
    r = libusb_init(&ctx);
    if (r < 0) {
        fprintf(stdout,"Ошибка: инициализация не выполнена, код: %d.\n", r);
        return 1;
    }
    // задать уровень подробности отладочных сообщений
    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, 3);
//    libusb_set_debug(ctx, 3);
    // получить список всех найденных USB- устройств
    cnt = libusb_get_device_list(ctx, &devs);
    if(cnt < 0){
        cout << "Ошибка: список USB устройств не получен.\n" << r;
        return 1;
    }
    cout << "найдено устройств: " << cnt << endl;
//    printf("=============================="
//           "=============================\n");
//    printf("* количество возможных конфигураций\n");
//    printf("| * класс устройства\n");
//    printf("| | * идентификатор производителя\n");
//    printf("| | | * идентификатор устройства\n");
//    printf("| | | | * количество интерфейсов\n");
//    printf("| | | | | * количество "
//           "альтернативных настроек\n");
//    printf("| | | | | | * класс устройства\n");
//    printf("| | | | | | | * номер интерфейса\n");
//    printf("| | | | | | | | * количество "
//           "конечных точек\n");
//    printf("| | | | | | | | | * тип дескриптора\n");
//    printf("| | | | | | | | | | * адрес "
//           "конечной точки\n");
//    printf("+--+--+----+----+---+--+--+--+"
//           "--+--+----------------------\n");
    for(i = 0; i < cnt; i++) { // цикл перебора всех устройств
        cout << "устройство " << i + 1 << endl;
        printdev(devs[i]);
        cout << "\n\n";// печать параметров устройства
    }
    printf("=============================="
           "=============================\n");
// освободить память, выделенную функцией получения списка устройств
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx); // завершить работу с библиотекой libusb,
// закрыть сессию работы с libusb
    return 0;
}
