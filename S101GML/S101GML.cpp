#include "S101GML.h"

#include "ATTR.h"
#include "CodeWithNumericCode.h"
#include "F_FASC.h"
#include "F_INAS.h"
#include "GeoCommonFuc.h"
#include "R_FeatureRecord.h"
#include "R_InformationRecord.h"
#include "S100Utilities.h"
#include "SCompositeCurve.h"
#include "SCurve.h"
#include "SSurface.h"
#include "SGeometry.h"
#include "SPoint.h"
#include <sstream>

#include <iomanip>
#include <iostream>

// ================

std::wstring S101GML::get_feature_id(int id, int ENCODING)
{
    wchar_t numChar[16];
    std::swprintf(numChar, sizeof(numChar)/sizeof(numChar[0]), L"%04d", id);
    std::wstringstream wss;
    wss << L"FEATURE_ID_" << std::setw(4) << numChar;
    return wss.str();
}

std::wstring S101GML::get_information_id(int id, int ENCODING)
{
    wchar_t numChar[16];
    std::swprintf(numChar, sizeof(numChar)/sizeof(numChar[0]), L"%04d", id);
    std::wstringstream wss;
    wss << L"INFO_ID_" << std::setw(4) << numChar;
    return wss.str();
}

std::string S101GML::get_feature_id_string(int id)
{
    char numChar[16];
    std::snprintf(numChar, sizeof(numChar), "%04d", id);
    std::stringstream ss;
    ss << "FEATURE_ID_" << std::setw(4) << numChar;
    return ss.str();
}

std::string S101GML::get_information_id_string(int id)
{
    char numChar[16];
    std::snprintf(numChar, sizeof(numChar), "%04d", id);
    std::stringstream ss;
    ss << "INFO_ID_" << std::setw(4) << numChar;
    return ss.str();
}

std::wstring S101GML::get_wstring_from_coordinate_1(int value)
{
    std::wstringstream wss;
    wss.setf(std::ios::fixed);
    wss.setf(std::ios::showpoint);
    wss.precision(7);

    wss << value / 10000000.;
    return wss.str();
}

// ================

void S101GML::ExportToGML(const libS101::S101 &s101cell, const libS101::String gmlPath){
    S101GML exporter(s101cell);
    pugi::xml_document doc = exporter.GmlDocMakeByPugi();
    try {
        auto xmlSaveError = doc.save_file(gmlPath);
    } catch (int e) {
        std::cout << "Save Fail " << e << std::endl;
    }
}

std::string S101GML::ExportToGML(const libS101::S101 &s101cell){
    S101GML exporter(s101cell);
    pugi::xml_document doc = exporter.GmlDocMakeByPugi();
   
    std::ostringstream oss;
    doc.save(oss);
    std::string xmlString = oss.str();
    return xmlString;
}

S101GML::S101GML(const libS101::S101 &s101cell): cell(s101cell){

}

pugi::xml_document S101GML::GmlDocMakeByPugi()
{
    pugi::xml_document doc = pugi::xml_document();
    auto declarationNode = doc.append_child(pugi::node_declaration);
    declarationNode.append_attribute("version") = "1.0";
    declarationNode.append_attribute("encoding") = "UTF-8";

    pugi::xml_node root;
    std::string productNamespace; // ex) S101, S124, S201 ...

    productNamespace = "S101";
    root = doc.append_child("S101:DataSet");
    root.append_attribute("xmlns:S101") = "http://www.iho.int/S101/gml/1.0";
    root.append_attribute("xsi:schemaLocation") = "http://www.iho.int/S-101/gml/1.0 ../../../schemas/S101/1.0/20170430/S101.xsd";
    root.append_attribute("xmlns:xsi") = "http://www.w3.org/2001/XMLSchema-instance";
    root.append_attribute("xmlns:xlink") = "http://www.w3.org/1999/xlink";
    root.append_attribute("xmlns:gml") = "http://www.opengis.net/gml/3.2";
    root.append_attribute("xmlns:S100") = "http://www.iho.int/s100gml/1.0";
    root.append_attribute("xmlns:s100_profile") = "http://www.iho.int/S-100/profile/s100_gmlProfile";
    root.append_attribute("gml:id") = "KRNPI101_TEST002_001";

    auto boundedBy = root.append_child("gml:boundedBy");
    auto Envelope = boundedBy.append_child("gml:Envelope");
    Envelope.append_attribute("srsName") = "EPSG:4326";
    Envelope.append_attribute("srsDimension") = "2";

    invMBR = cell.mbr;
    inverseProjection(invMBR);

    std::wstring strX = get_wstring_from_coordinate_1((int)(invMBR.xmin * cell.m_dsgir.m_dssi.m_cmfx));
    std::wstring strY = get_wstring_from_coordinate_1((int)(invMBR.ymin * cell.m_dsgir.m_dssi.m_cmfy));
    std::wstring strCoordi = strX + L" " + strY;
    std::string cStrCoordi = pugi::as_utf8(strCoordi);

    pugi::xml_node lowerCorner = Envelope.append_child("gml:lowerCorner");
    lowerCorner.append_child(pugi::node_pcdata).set_value(cStrCoordi.c_str());

    strX = get_wstring_from_coordinate_1((int)(invMBR.xmax * cell.m_dsgir.m_dssi.m_cmfx));
    strY = get_wstring_from_coordinate_1((int)(invMBR.ymax * cell.m_dsgir.m_dssi.m_cmfy));

    strCoordi = strX + L" " + strY;
    cStrCoordi = pugi::as_utf8(strCoordi);

    pugi::xml_node upperCorner = Envelope.append_child("gml:upperCorner");
    upperCorner.append_child(pugi::node_pcdata).set_value(cStrCoordi.c_str());

#pragma region DatasetIdentificationInformation

    pugi::xml_node DatasetIdentificationInformation = root.append_child("DatasetIdentificationInformation");

    pugi::xml_node EncodingSpecification = DatasetIdentificationInformation.append_child("S100:encodingSpecification");
    EncodingSpecification.append_child(pugi::node_pcdata).set_value(cell.GetEncodingSpecificationToString().c_str());

    pugi::xml_node EncodingSpecificationEdication = DatasetIdentificationInformation.append_child("S100:encodingSpecificationEdition");
    EncodingSpecificationEdication.append_child(pugi::node_pcdata).set_value(cell.GetEncodingSpecificationEditionToString().c_str());

    pugi::xml_node productIdentifier = DatasetIdentificationInformation.append_child("S100:productIdentifier");
    productIdentifier.append_child(pugi::node_pcdata).set_value(cell.GetProductIdentifierToString().c_str());

    pugi::xml_node productEdition = DatasetIdentificationInformation.append_child("S100:productEdition");
    productEdition.append_child(pugi::node_pcdata).set_value(cell.GetProductEditionToString().c_str());

    pugi::xml_node applicationProfile = DatasetIdentificationInformation.append_child("S100:applicationProfile");
    applicationProfile.append_child(pugi::node_pcdata).set_value(cell.GetApplicationProfileToString().c_str());

    std::string fileName(cell.GetFileName().str());
    pugi::xml_node datasetFileIdentifier = DatasetIdentificationInformation.append_child("S100:datasetFileIdentifier");
    datasetFileIdentifier.append_child(pugi::node_pcdata).set_value(cell.GetDatasetFileIdentifierToString().c_str());


    pugi::xml_node datasetTitle = DatasetIdentificationInformation.append_child("S100:datasetTitle");
    datasetTitle.append_child(pugi::node_pcdata).set_value(cell.GetDatasetTitleToString().c_str());


    pugi::xml_node datasetReferenceDate = DatasetIdentificationInformation.append_child("S100:datasetReferenceDate");
    datasetReferenceDate.append_child(pugi::node_pcdata).set_value(cell.GetDatasetReferenceDataToString().c_str());

    pugi::xml_node datasetLanguage = DatasetIdentificationInformation.append_child("S100:datasetLanguage");
    datasetLanguage.append_child(pugi::node_pcdata).set_value(cell.GetDatasetLanguageToString().c_str());

    pugi::xml_node datasetAbstract = DatasetIdentificationInformation.append_child("S100:datasetAbstract");
    datasetAbstract.append_child(pugi::node_pcdata).set_value(cell.GetDatasetAbstractToString().c_str());

    pugi::xml_node datasetEdition = DatasetIdentificationInformation.append_child("S100:datasetEdition");
    datasetEdition.append_child(pugi::node_pcdata).set_value(cell.GetDatasetEditionToString().c_str());

    pugi::xml_node datasetTopicCategory = DatasetIdentificationInformation.append_child("S100:datasetTopicCategory");
    datasetTopicCategory.append_child(pugi::node_pcdata).set_value("utilitiesCommunication");


#pragma endregion 
#pragma region DatasetStructureInformation

    pugi::xml_node DatasetStructureInformation = root.append_child("DatasetStructureInformation");

    pugi::xml_node DatasetCoordOriginX = DatasetStructureInformation.append_child("S100:datasetCoordOriginX");
    DatasetCoordOriginX.append_child(pugi::node_pcdata).set_value("0.0");

    pugi::xml_node DatasetCoordOriginY = DatasetStructureInformation.append_child("S100:datasetCoordOriginY");
    DatasetCoordOriginY.append_child(pugi::node_pcdata).set_value("0.0");

    pugi::xml_node DatasetCoordOriginZ = DatasetStructureInformation.append_child("S100:datasetCoordOriginZ");
    DatasetCoordOriginZ.append_child(pugi::node_pcdata).set_value("0.0");

    pugi::xml_node coordMultFactorX = DatasetStructureInformation.append_child("S100:coordMultFactorX");
    coordMultFactorX.append_child(pugi::node_pcdata).set_value("1");

    pugi::xml_node coordMultFatcorY = DatasetStructureInformation.append_child("S100:coordMultFactorY");
    coordMultFatcorY.append_child(pugi::node_pcdata).set_value("1");

    pugi::xml_node coordMultFatcorZ = DatasetStructureInformation.append_child("S100:coordMultFactorZ");
    coordMultFatcorZ.append_child(pugi::node_pcdata).set_value("1");
#pragma endregion

    SetInformationsType(&doc, root, productNamespace);
    SetFeaturesType(&doc, root, productNamespace);

#pragma region RELATION
    SetFeaturesTypeRelation_v2(root);
    SetInformationsTypeRelation_v2(root);
#pragma endregion 

    return doc;
}

void S101GML::SetInformationsType(pugi::xml_document* doc, pugi::xml_node parentNode, std::string productNamespace)
{
    for (auto itor = cell.vecInformation.begin(); itor != cell.vecInformation.end(); itor++)
    {
        R_InformationRecord* ir = *(itor);
        libS101::String informationAcronym = cell.m_dsgir.m_itcs->m_arr.find(ir->m_irid.m_nitc)->second->m_code;
        pugi::xml_node imember = parentNode.append_child("imember");

        auto featureElementName = productNamespace + ":" + informationAcronym.str();
        pugi::xml_node informationNode = imember.append_child(featureElementName.c_str());

        std::string iid = get_information_id_string(ir->m_irid.m_name.RCID);

        informationNode.append_attribute("gml:id") = iid.c_str();

        objectPugiXmlElementMap.insert(std::unordered_map<std::string, pugi::xml_node*>::value_type(iid, &informationNode));
        SetAttributeType(doc, informationNode, &ir->m_attr);
    }
}

void S101GML::SetFeaturesType(pugi::xml_document* document, pugi::xml_node parentNode, std::string productNamespace)
{
    for (auto itor = cell.vecFeature.begin(); itor != cell.vecFeature.end(); itor++)
    {
        R_FeatureRecord* fr = *(itor);
        auto what = cell.m_dsgir.m_ftcs->m_arr.find(fr->m_frid.m_nftc);

        pugi::xml_node member = parentNode.append_child("member");

        libS101::String featureAcronym = cell.m_dsgir.m_ftcs->m_arr.find(fr->m_frid.m_nftc)->second->m_code;

        auto featureElementName = productNamespace + ":" + pugi::as_utf8(std::wstring(featureAcronym));

        pugi::xml_node pFeatureNode = member.append_child(featureElementName.c_str());


        std::string iid = get_feature_id_string(fr->m_frid.m_name.RCID);
        pFeatureNode.append_attribute("gml:id") = iid.c_str();
        objectPugiXmlElementMap.insert({ iid, &pFeatureNode });

        SetAttributeType(document, pFeatureNode, &fr->m_attr);
        SetVector(pFeatureNode, fr);
    }
}

void S101GML::SetFeaturesTypeRelation_v2(pugi::xml_node rootNode)
{
    pugi::xml_node* pFeatureNode = nullptr;
    for (auto itor = cell.vecFeature.begin(); itor != cell.vecFeature.end(); itor++)
    {
        R_FeatureRecord* fr = *(itor);
        std::string srcFeatureID = get_feature_id_string(fr->m_frid.m_name.RCID);

        auto srcFeatureXpath = "/S201:DataSet/member/S201:*[@gml:id='" + srcFeatureID + "']";
        auto srcFeatureElement = rootNode.select_node(srcFeatureXpath.c_str());


        if (srcFeatureElement.node())
        {
            auto featureNode = srcFeatureElement.node();
            pFeatureNode = &featureNode;
        }
        else
        {
            continue;
        }

        for (auto i = fr->m_fasc.begin(); i != fr->m_fasc.end(); i++)
        {
            F_FASC* f_fasc = *i;
            std::int64_t key = ((std::int64_t)100) << 32 | f_fasc->m_name.RCID;
            std::string iid = get_feature_id_string(fr->m_frid.m_name.RCID);

            auto dstFeatureXpath = "/S201:DataSet/member/S201:*[@gml:id='" + iid + "']";

            auto dstFeatureElement = rootNode.select_node(dstFeatureXpath.c_str());
            if (dstFeatureElement.node() == nullptr)
            {
                continue;
            }

            auto node = dstFeatureElement.node();

            pugi::xml_node* dstFeatureNode = &node;
            std::string dstFeatureID = "#" + iid;


            auto ritor = cell.m_dsgir.m_arcs->m_arr.find(f_fasc->m_nfac);

            auto roleName = ritor->second->m_code;

            auto roleNode = pFeatureNode->append_child(pugi::as_utf8(std::wstring(roleName)).c_str());
            dstFeatureNode = &roleNode;
            dstFeatureNode->append_attribute("xlink:href") = dstFeatureID.c_str();


            for (auto itorParent = fr->m_inas.begin(); itorParent != fr->m_inas.end(); itorParent++)
            {
                F_INAS* f_inas = *itorParent;
                std::string iid = get_information_id_string(f_inas->m_name.RCID);
                auto itor = objectPugiXmlElementMap.find(iid);
                pugi::xml_node* pElement = itor->second;

                std::string eid = "#";

                pugi::xml_attribute pAttrib;
                pAttrib = pElement->first_attribute();

                if (pAttrib == nullptr)
                {
                    return;
                }

                while (pAttrib)
                {
                    std::string attrName = pAttrib.name();
                    if (attrName.compare("gml:id"))
                    {
                        eid.append(pAttrib.value());
                        break;
                    }
                    pAttrib = pAttrib.next_attribute();
                }

                auto asitor = cell.m_dsgir.m_iacs->m_arr.find(f_inas->m_niac);
                auto ritor = cell.m_dsgir.m_arcs->m_arr.find(f_inas->m_niac);
                auto roleName = ritor->second->m_code;

                auto node = pFeatureNode->append_child("S100:informationAssociation");
                pElement = &node;
                pElement->append_attribute("xlink:role") = roleName;
                pElement->append_attribute("xlink:href") = eid.c_str();
            }
        }

    }
}

void S101GML::SetInformationsTypeRelation_v2(pugi::xml_node parentNode)
{
    for (auto itor = cell.vecInformation.begin(); itor != cell.vecInformation.end(); itor++)
    {
        R_InformationRecord* ir = *(itor);

        std::string iid;
        auto it = objectPugiXmlElementMap.find(iid);
        if (it == objectPugiXmlElementMap.end())
        {
            continue;
        }

        pugi::xml_node* pInformationNode = it->second;

        for (auto itorParent = ir->m_inas.begin(); itorParent != ir->m_inas.end(); itorParent++)
        {
            F_INAS* f_inas = *itorParent;

            std::string iid = get_information_id_string(f_inas->m_name.RCID);

            auto itor = objectPugiXmlElementMap.find(iid);

            pugi::xml_node* pElement = itor->second;
            std::string eid = "#";

            pugi::xml_attribute* pAttrib;
            auto node = pElement->first_attribute();
            pAttrib = &node;

            while (pAttrib)
            {
                std::string attrName = pAttrib->name();

                if (attrName.compare("gml:id") == 0)
                {
                    eid.append(pAttrib->value());
                    break;
                }

                auto node = pAttrib->next_attribute();
                pAttrib = &node;
            }

            auto asitor = cell.m_dsgir.m_iacs->m_arr.find(f_inas->m_niac);
            auto ritor = cell.m_dsgir.m_arcs->m_arr.find(f_inas->m_narc);
            auto roleName = ritor->second->m_code;

            auto infoAsscoiNode = pInformationNode->append_child("S100:informationAssocination");
            pElement = &infoAsscoiNode;
            pElement->append_attribute("xlink:role") = roleName;
            pElement->append_attribute("xlink:href") = eid.c_str();
        }
    }
}

void S101GML::SetAttributeType(pugi::xml_document* doc, pugi::xml_node parentNode, std::list<F_ATTR*>* f_attrList)
{
    std::unordered_map<int, pugi::xml_node> attrXmlNodeMap;

    for (auto itorParent = f_attrList->begin(); itorParent != f_attrList->end(); itorParent++)
    {
        F_ATTR* attr = *itorParent;
        int index = 0;
        attrXmlNodeMap.clear();

        for (auto aitor = attr->m_arr.begin(); aitor != attr->m_arr.end(); aitor++)
        {
            index++;
            ATTR* attr = *aitor;

            auto itor = cell.m_dsgir.m_atcs->m_arr.find(attr->m_natc);
            if (itor == cell.m_dsgir.m_atcs->m_arr.end())
            {
                continue;
            }

            std::wstring attributeName = std::wstring(itor->second->m_code);
            pugi::xml_node pElement = doc->append_child(libS101::String(attributeName).c_str());

            attrXmlNodeMap.insert(std::unordered_map<int, pugi::xml_node>::value_type(index, pElement));

            if (attr->m_atvl.empty()) // complex
            {
                if (attr->m_paix == 0)
                {
                    parentNode.append_move(pElement);
                }
                else
                {
                    auto itor = attrXmlNodeMap.find(attr->m_paix);
                    pugi::xml_node parent = itor->second;
                    parent.append_move(pElement);
                }
            }
            else //simple
            {
                std::string inputText = "";
                inputText = pugi::as_utf8(attr->m_atvl);

                if (attr->m_paix == 0) //���� �׳� �߰��Ұ��
                {
                    parentNode.append_move(pElement);
                    pElement.append_child(pugi::node_pcdata).set_value(inputText.c_str());
                }
                else
                {
                    auto itor = attrXmlNodeMap.find(attr->m_paix);
                    if (itor != attrXmlNodeMap.end())
                    {
                        pElement.append_child(pugi::node_pcdata).set_value(inputText.c_str());
                        pugi::xml_node parent = itor->second;
                        auto ischild = parent.append_move(pElement);
                        if (!ischild)
                        {
                            S100Utilities::OutputDebugString(L"�ڽ�ȭ�� �����߽��ϴ�.");
                        }
                    }

                }
            }
        }
    }
}


void S101GML::SetVector(pugi::xml_node parentNode, R_FeatureRecord* fr)
{
    if (fr->m_geometry == nullptr)
    {
        return;
    }

    auto type = fr->m_geometry->type;
    if (type == 1)
    {
        SetVectorPointsType(parentNode, (SPoint*)fr->m_geometry);
    }
    else if (type == 2)
    {
        SetVectorCompositeCurvesType(parentNode, (SCompositeCurve*)fr->m_geometry);
    }
    else if (type == 3)
    {
        SetVectorSurfacesType(parentNode, (SSurface*)fr->m_geometry);
    }
    else if (type == 4)
    {
        SetVectorMultiPointsType(parentNode, (SMultiPoint*)fr->m_geometry);
    }
}

void S101GML::SetVectorPointsType(pugi::xml_node parentNode, SPoint* p)
{
    std::wstring coordinateString;
    double x, y;
    x = p->m_point.x;
    y = p->m_point.y;
    inverseProjection(x, y);

    std::wstring strX = get_wstring_from_coordinate_1((int)(x * cell.m_dsgir.m_dssi.m_cmfx));
    std::wstring strY = get_wstring_from_coordinate_1((int)(y * cell.m_dsgir.m_dssi.m_cmfy));

    coordinateString.append(strX);
    coordinateString.append(L" ");
    coordinateString.append(strY);

    pugi::xml_node geometry = parentNode.append_child("geometry");
    pugi::xml_node pointProperty = geometry.append_child("S100:pointProperty");
    static int poiontID = 1;

    pugi::xml_node point = pointProperty.append_child("S100:Point");
    point.append_attribute("gml:id").set_value((poiontID++));

    pugi::xml_node pos = point.append_child("gml:pos");
    pos.append_child(pugi::node_pcdata).set_value(libS101::String(coordinateString).c_str());
}

void S101GML::SetVectorMultiPointsType(pugi::xml_node parentNode, SMultiPoint* p)
{

}

void S101GML::SetVectorCurvesType(pugi::xml_node parentNode, SCurve* p)
{
    std::wstring coordinateString;
    for (int i = 0; i < p->m_numPoints; i++)
    {
        double x, y;

        x = p->m_pPoints[i].x;
        y = p->m_pPoints[i].y;
        inverseProjection(x, y);

        std::wstring strX = get_wstring_from_coordinate_1((int)(x * cell.m_dsgir.m_dssi.m_cmfx));
        std::wstring strY = get_wstring_from_coordinate_1((int)(y * cell.m_dsgir.m_dssi.m_cmfx));

        coordinateString.append(strX);
        coordinateString.append(L" ");
        coordinateString.append(strY);

        if (i = !p->m_numPoints)
        {
            coordinateString.append(L" ");
        }
    }

    pugi::xml_node pGeometry = parentNode.append_child("geometry");
    pugi::xml_node pCurveProperty = pGeometry.append_child("S100:curveProperty");
    pugi::xml_node pCurve = pCurveProperty.append_child("gml:Curve");
    pCurve.append_attribute("srsName") = "http://www.opengis.net/gml/srs/epsg.xml#4326";

    static int curveID = 1;

    pCurve.append_attribute("gml:id") = curveID++;

    pugi::xml_node pSegments = pCurve.append_child("gml:segments");
    pugi::xml_node pLineString = pSegments.append_child("gml:LineString");
    pugi::xml_node pPosList = pLineString.append_child("gml:posList");
    pPosList.append_child(pugi::node_pcdata).set_value(libS101::String(coordinateString).c_str());
}

void S101GML::SetVectorCompositeCurvesType(pugi::xml_node parentNode, SCompositeCurve* p)
{
    auto curvelist = &p->m_listCurveLink;
    for (auto iter = curvelist->begin(); iter != curvelist->end(); iter++)
    {
        SCurveHasOrient* curveOrient = &(*iter);

        pugi::xml_node pGeometry = parentNode.append_child("geometry");
        pugi::xml_node pCurveProperty = pGeometry.append_child("S100:curveProperty");
        pugi::xml_node pCurve = pCurveProperty.append_child("gml:Curve");
        pCurve.append_attribute("srsName") = "http://www.opengis.net/gml/srs/epsg.xml#4326";
        static int curveID = 1;
        std::wstring coordinateString;


        auto curve = curveOrient->GetCurve();
        if (curveOrient->GetMasking() == true)
        {
            //for (int j = 0; j < numPoint; j++)
            //{
            //	double x = curve->GetX(j);
            //	double y = curve->GetY(j);
            //	inverseProjection(x, y);

            //	std::wstring strX = get_wstring_from_coordinate_1((int)(x*m_dsgir.m_dssi.m_cmfx));
            //	std::wstring strY = get_wstring_from_coordinate_1((int)(y*m_dsgir.m_dssi.m_cmfx));

            //	coordinateString.append(strX);
            //	coordinateString.append(L" ");
            //	coordinateString.append(strY);

            //	if (j != curve->m_numPoints -1)
            //	{
            //		coordinateString.append(L" ");
            //	}
            //}
        }
        else if (curveOrient->GetMasking() == false)
        {
            bool curOrient = true;
            bool parentOrient = curveOrient->GetParentOrient();

            if (parentOrient == false)
            {
                curOrient = !curOrient;
            }

            int numPoint = curve->GetNumPoints();
            if (!curOrient)
            {
                for (int j = numPoint - 1; j >= 0; j--)
                {
                    double x = curve->GetX(j);
                    double y = curve->GetY(j);
                    inverseProjection(x, y);

                    std::wstring strX = get_wstring_from_coordinate_1((int)(x * cell.m_dsgir.m_dssi.m_cmfx));
                    std::wstring strY = get_wstring_from_coordinate_1((int)(y * cell.m_dsgir.m_dssi.m_cmfx));

                    coordinateString.append(strX);
                    coordinateString.append(L" ");
                    coordinateString.append(strY);

                    if (j != 0)
                    {
                        coordinateString.append(L" ");
                    }
                }
            }
            else
            {
                for (int j = 0; j < numPoint - 1; j++)
                {
                    double x = curve->GetX(j);
                    double y = curve->GetY(j);
                    inverseProjection(x, y);

                    std::wstring strX = get_wstring_from_coordinate_1((int)(x * cell.m_dsgir.m_dssi.m_cmfx));
                    std::wstring strY = get_wstring_from_coordinate_1((int)(y * cell.m_dsgir.m_dssi.m_cmfx));

                    coordinateString.append(strX);
                    coordinateString.append(L" ");
                    coordinateString.append(strY);

                    if (j != numPoint - 1)
                    {
                        coordinateString.append(L" ");
                    }
                }
            }
        }


        pCurve.append_attribute("gml:id") = curveID++;

        pugi::xml_node pSegments = pCurve.append_child("gml:segments");
        pugi::xml_node pLineString = pSegments.append_child("gml:LineString");
        pugi::xml_node pPosList = pLineString.append_child("gml:posList");
        pPosList.append_child(pugi::node_pcdata).set_value(libS101::String(coordinateString).c_str());
    }
}

void S101GML::SetVectorSurfacesType(pugi::xml_node parentnode, SSurface* p)
{
    std::wstring outboundCoordinateString;
    std::vector<std::wstring> inboundCoorinateStringList;
    for (int pi = 0; pi < p->m_numParts; pi++)
    {
        int curMaxIndex = 0;

        if (pi + 1 == p->m_numParts)
        {
            curMaxIndex = p->m_numPoints;
        }
        else
        {
            curMaxIndex = p->m_pParts[pi + 1];
        }

        if (pi == 0)
        {
            for (int i = 0; i < curMaxIndex; i++)
            {
                double x, y;
                x = p->m_pPoints[i].x;
                y = p->m_pPoints[i].y;

                inverseProjection(x, y);
                std::wstring strX = get_wstring_from_coordinate_1((int)(x * cell.m_dsgir.m_dssi.m_cmfx));
                std::wstring strY = get_wstring_from_coordinate_1((int)(y * cell.m_dsgir.m_dssi.m_cmfy));

                outboundCoordinateString.append(strX);
                outboundCoordinateString.append(L" ");
                outboundCoordinateString.append(strY);

                if (i != p->m_numPoints)
                {
                    outboundCoordinateString.append(L" ");
                }
            }
        }
        else
        {
            std::wstring inboundCoordinateString;
            if (pi == p->m_numParts - 1)
            {
                curMaxIndex++;
            }

            for (int i = p->m_pParts[pi]; i < curMaxIndex - 1; i++)
            {
                double x, y;
                x = p->m_pPoints[i].x;
                y = p->m_pPoints[i].y;

                inverseProjection(x, y);

                std::wstring strX = get_wstring_from_coordinate_1((int)(x * cell.m_dsgir.m_dssi.m_cmfx));
                std::wstring strY = get_wstring_from_coordinate_1((int)(y * cell.m_dsgir.m_dssi.m_cmfy));

                inboundCoordinateString.append(strX);
                inboundCoordinateString.append(L" ");
                inboundCoordinateString.append(strY);

                if (i != p->m_numPoints)
                {
                    inboundCoordinateString.append(L" ");
                }
            }
            inboundCoorinateStringList.push_back(inboundCoordinateString);
        }
    }


    pugi::xml_node pGeometry = parentnode.append_child("geometry");
    pugi::xml_node pSurfaceProperty = pGeometry.append_child("S100:surfaceProperty");

    static int surfaceID = 1;
    pugi::xml_node pSurface = pSurfaceProperty.append_child("S100:Surface");
    pSurface.append_attribute("gml:id") = surfaceID++;

    pugi::xml_node pPatches = pSurface.append_child("gml:patches");
    pugi::xml_node pPolygonPatch = pPatches.append_child("gml:PolygonPatch");
    pugi::xml_node pExterior = pPolygonPatch.append_child("gml:exterior");
    pugi::xml_node pLinerRing = pExterior.append_child("gml:LinearRing");
    pugi::xml_node pPosList = pLinerRing.append_child("gml:posList");
    pPosList.append_child(pugi::node_pcdata).set_value(libS101::String(outboundCoordinateString).c_str());

    for (unsigned i = 0; i < inboundCoorinateStringList.size(); i++)
    {
        std::wstring ibc = inboundCoorinateStringList[i];

        pugi::xml_node pIterior = pPolygonPatch.append_child("gml:interior");
        pugi::xml_node pLinearRing = pIterior.append_child("gml:LinearRing");
        pugi::xml_node posList = pLinearRing.append_child("gml:posList");
        posList.append_child(pugi::node_pcdata).set_value(libS101::String(ibc).c_str());
    }
}