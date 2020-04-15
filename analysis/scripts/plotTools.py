# -*- coding: utf-8 -*-
import ROOT as r
from ROOT import gStyle, gROOT
from copy import deepcopy
import sys
from markers import markerColors, markerTypes
r.gROOT.SetBatch(True)



############################################# CHANGE IF NECESSARY ###########################################################

#############################################################################################################################

def makePlot(hlist, path, files, plotscaffold, merge, normalize):
    
    if not merge :
      res = r.TFile.Open(path + files)
      resplot = res.Get(plotscaffold)
    else :
      #res = r.TFile.Open(path+files[0]+'.root')
      res = files[0]
      resplot = res.Get(plotscaffold)
      for i in range (1,len(files)) :
        otherFile = files[i]
        #otherFile = r.TFile.Open(path+files[i]+'.root')
        otherPlot = otherFile.Get(plotscaffold)
        resplot.Add(otherPlot)
        #otherFile.Close();
        del otherPlot

    if normalize==1 and resplot.Integral() > 0 : resplot.Scale (1. / resplot.Integral() )
    elif normalize>1 : resplot.Scale (normalize)


    hlist.append(deepcopy(resplot))
    if merge : del resplot
    if not merge : res.Close(); del res, resplot
    #res.Close(); del res, resplot
    return

def combinePlots (hlist, legends, plottingStuff, path, savescaffold, logy=False): 
    print "Combining list of plots"
    if len(hlist) == 0: raise RuntimeError("Empty list of plots")
    c   = r.TCanvas("c", "c", 800, 800)

    maxim = -1; 

    gStyle.SetOptStat(0)
    leg = r.TLegend(plottingStuff['legxlow'], plottingStuff['legylow'], plottingStuff['legxhigh'], plottingStuff['legyhigh'])
    for iplot in range(len(hlist)):
        hlist[iplot].SetMarkerColor(markerColors[iplot % len(markerColors)])
        #hlist[iplot].SetMarkerColor(plottingStuff['markercolordir'][hlist[iplot].GetName()])
        hlist[iplot].SetLineColor(markerColors[iplot % len(markerColors)])
        #hlist[iplot].SetLineColor(plottingStuff['markercolordir'][hlist[iplot].GetName()])
        hlist[iplot].SetMarkerStyle(20)
        hlist[iplot].SetLineStyle(1 + iplot / len(markerColors))
#        hlist[iplot].SetMarkerStyle(markerTypes[iplot / len(markerColors)])
        #hlist[iplot].SetMarkerStyle(plottingStuff['markertypedir'][hlist[iplot].GetName()])
        leg.AddEntry(hlist[iplot], legends[iplot], "PL")
        hlist[iplot].Draw("histosame")
        if ( hlist[iplot].GetMaximum() > maxim ) : 
          hlist[0].GetYaxis().SetRangeUser(0.0001, hlist[iplot].GetMaximum()*1.5)
          maxim = hlist[iplot].GetMaximum()
        #hlist[iplot].Draw("P" + (iplot == 0) * "A" + (iplot != 0) * "same")

    leg.Draw()
   
    r.gPad.Update()
    #hlist[0].GetYaxis().SetRangeUser(plottingStuff['lowlimityaxis'], plottingStuff['highlimityaxis'])
    
    firsttex = r.TLatex()
    firsttex.SetTextSize(0.03)
    firsttex.DrawLatexNDC(0.11,0.91,"#scale[1.5]{CMS} Preliminary")
    firsttex.Draw("same");

    secondtext = r.TLatex()
    toDisplay = r.TString()
    toDisplay  = r.TString("60.0 fb^{-1} 13 TeV")
    secondtext.SetTextSize(0.035)
    secondtext.SetTextAlign(31)
    secondtext.DrawLatexNDC(0.90, 0.91, toDisplay.Data())
    secondtext.Draw("same")


    if logy: c.SetLogy()

    if not logy : c.SaveAs(path + savescaffold + ".png")
    else : c.SaveAs(path + savescaffold + "_logy.png")
    if not logy : c.SaveAs(path + savescaffold + ".pdf")
    else : c.SaveAs(path + savescaffold + "_logy.pdf")
    #if not logy : c.SaveAs(path + savescaffold + ".root")
    #else c.SaveAs(path + savescaffold + "_logy.root")
    
    c.Close(); del c



def dataMCPlots (dataPlot, MClist, MClegends, plottingStuff, path, savescaffold, logy=False): 
    print "Combining list of plots"
    if len(MClist) == 0 or len(dataPlot) == 0: raise RuntimeError("Empty list of plots")
    #c   = r.TCanvas("c", "c", 800, 800)
    c   = r.TCanvas("c","c",10,10,1000,1000);
    #c.Divide(1,2,0,0)
    pad1 = r.TPad("pad1", "The pad 70% of the height",0.0,0.3,1.0,1.0,31);
    pad2 = r.TPad("pad2", "The pad 30% of the height",0.0,0.0,1.0,0.3,32);

    pad1.SetFillColor(r.kWhite);
    pad2.SetFillColor(r.kWhite);
    pad1.Draw();
    pad2.Draw("same");
    pad1.cd();
    pad1.SetBottomMargin(0.1);
    #pad1.SetLeftMargin(0.2);

    maxim = -1; 

    gStyle.SetOptStat(0)
    leg = r.TLegend(plottingStuff['legxlow'], plottingStuff['legylow'], plottingStuff['legxhigh'], plottingStuff['legyhigh'])
    
    hs = r.THStack("hs","")
    nEntries = 0
    for iplot in range(len(MClist)):
        MClist[iplot].SetFillColor(markerColors[iplot % len(markerColors)])
        nEntries += MClist[iplot].Integral()
        leg.AddEntry(MClist[iplot], MClegends[iplot], "f")

    dataPlot[0].SetMarkerColor(r.kBlack)
    dataPlot[0].SetMarkerSize(1)
    dataPlot[0].SetMarkerStyle(20)
    dataPlot[0].SetLineColor(r.kBlack)
    leg.AddEntry(dataPlot[0], "data", "PL")
    
    #hs.Scale(dataPlot[0].Integral() / hs.Integral() )
    for iplot in range(len(MClist)):
      #if dataPlot[0].Integral() > 0 : MClist[iplot].Scale( dataPlot[0].Integral() / nEntries )
      if iplot == 0 : h = MClist[iplot].Clone()
      else : h.Add(MClist[iplot])
      hs.Add(MClist[iplot])

    preliminary = r.TLatex(0.11,0.91,"    #scale[1.5]{CMS} preliminary");
    preliminary.SetTextSize(0.03)
    preliminary.SetNDC();
    #preliminary.SetTextFont(42);

    #c.Divide(1,2,0,0);
    pad1.cd();
    #c.GetPad(1).SetBottomMargin(0.1)
    dataPlot[0].Draw("e")
    hs.Draw("histoFsame")
    leg.SetFillColor(4001)
    leg.SetBorderSize(0)
    leg.SetNColumns(2)
    leg.Draw("same")
    preliminary.Draw();

    r.gPad.SetTicks(1,1);
    r.gPad.RedrawAxis();

    hD = dataPlot[0].Clone()
    hD.Divide(h)
    hD.GetYaxis().SetRangeUser(0.5,1.5)
    hD.GetYaxis().SetNdivisions(4)
    hD.GetYaxis().SetTitleOffset(0.45);
    hD.SetLabelSize(0.08, "xy");
    hD.SetTitleSize(0.08, "xy");
    pad2.cd(); 
    pad2.SetGrid()
    hD.SetTitle(" ; ; Data/MC")
    hD.Draw()

    
    

    #hlist[0].GetYaxis().SetRangeUser(plottingStuff['lowlimityaxis'], plottingStuff['highlimityaxis'])
    
    #firsttex = r.TLatex()
    #firsttex.SetTextSize(0.03)
    #firsttex.DrawLatexNDC(0.11,0.91,"#scale[1.5]{CMS} Preliminary")
    #firsttex.Draw("same");

    #secondtext = r.TLatex()
    #toDisplay = r.TString()
    #toDisplay  = r.TString("60.0 fb^{-1} 13 TeV")
    #secondtext.SetTextSize(0.035)
    #secondtext.SetTextAlign(31)
    #secondtext.DrawLatexNDC(0.90, 0.91, toDisplay.Data())
    #secondtext.Draw("same")


    if logy: c.SetLogy()

    if not logy : c.SaveAs(path + savescaffold + ".png")
    else : c.SaveAs(path + savescaffold + "_logy.png")
    if not logy : c.SaveAs(path + savescaffold + ".pdf")
    else : c.SaveAs(path + savescaffold + "_logy.pdf")
    #if not logy : c.SaveAs(path + savescaffold + ".root")
    #else c.SaveAs(path + savescaffold + "_logy.root")
    
    c.Close(); del c





